#ifndef _PNG2ASSET_H
#define _PNG2ASSET_H

#define RGBA32_SZ 4 // RGBA 8:8:8:8 is 4 bytes per pixel

#define ATTRIB_TILE_DIVIDE_NES_2         2 // 16x16 attributes with 8x8 tiles
#define ATTRIB_PACKED_TILE_DIVIDE_NES_4  4 // 32x32 blocks containing 16x16 attribute regions over 8x8 tiles
#define ATTRIBUTE_HEIGHT_NES            15
#define ATTRIBUTE_ALIGNED_HEIGHT_NES    16

enum {
    SPR_NONE,
    SPR_8x8,
    SPR_8x16,
    SPR_16x16_MSX
};

#define BIT(VALUE, INDEX) (1 & ((VALUE) >> (INDEX)))

struct Tile
{
    vector< unsigned char > data;
    unsigned char pal;

    Tile(size_t size = 0) : data(size), pal(0) {}
    bool operator==(const Tile& t) const
    {
        return data == t.data && pal == t.pal;
    }

    const Tile& operator=(const Tile& t)
    {
        data = t.data;
        pal = t.pal;
        return *this;
    }

    enum PackMode {
        GB,
        SGB,
        SMS,
        BPP1
    };

    vector< unsigned char > GetPackedData(PackMode pack_mode, int tile_w, int tile_h, int bpp) {
        vector< unsigned char > ret((tile_w / 8) * tile_h * bpp, 0);
        if(pack_mode == GB) {
            for(int j = 0; j < tile_h; ++j) {
                for(int i = 0; i < 8; ++ i) {
                    unsigned char col = data[8 * j + i];
                    ret[j * 2    ] |= BIT(col, 0) << (7 - i);
                    ret[j * 2 + 1] |= BIT(col, 1) << (7 - i);
                }
            }
        }
        else if(pack_mode == SGB)
        {
            for(int j = 0; j < tile_h; ++j) {
                for(int i = 0; i < 8; ++ i) {
                    unsigned char col = data[8 * j + i];
                    ret[j * 2    ] |= BIT(col, 0) << (7 - i);
                    ret[j * 2 + 1] |= BIT(col, 1) << (7 - i);
                    ret[(tile_h + j) * 2    ] |= BIT(col, 2) << (7 - i);
                    ret[(tile_h + j) * 2 + 1] |= BIT(col, 3) << (7 - i);
                }
            }
        }
        else if(pack_mode == SMS)
        {
            for(int j = 0; j < tile_h; ++j) {
                for(int i = 0; i < 8; ++ i) {
                    unsigned char col = data[8 * j + i];
                    ret[j * 4    ] |= BIT(col, 0) << (7 - i);
                    ret[j * 4 + 1] |= BIT(col, 1) << (7 - i);
                    ret[j * 4 + 2] |= BIT(col, 2) << (7 - i);
                    ret[j * 4 + 3] |= BIT(col, 3) << (7 - i);
                }
            }
        }
        else if(pack_mode == BPP1)
        {
            // Packs 8 pixel wide rows in order set by ExtractTile**()
            // Process all rows of pixels in the tile
            for(int j = 0; j < ((tile_w / 8) * tile_h); j++) {
                // Pack each row of 8 pixels into one byte
                for(int i = 0; i < 8; i++) {
                    unsigned char col = data[8 * j + i];
                    ret[j] |= BIT(col, 0) << (7 - i);
                }
            }
        }
        return ret;
    }
};

struct PNGImage
{
    vector< unsigned char > data; //data in indexed format
    unsigned int w;
    unsigned int h;

    bool use_nes_attributes = false;

    // Default tile size
    int tile_w = 8;
    int tile_h = 16;

    int map_attributes_divide_w = 1;
    int map_attributes_divide_h = 1;

    int    map_attributes_tile_w() const { return (tile_w * map_attributes_divide_w); }
    int    map_attributes_tile_h() const { return (tile_h * map_attributes_divide_h); }
    size_t map_attributes_width()  const { return (w / map_attributes_tile_w()); }
    size_t map_attributes_height() const { return (h / map_attributes_tile_h()); }

    // For all platforms except NES the below are the same as map_attributes_width/height
    //
    // For NES this is post-alignment
    size_t map_attributes_final_width;
    size_t map_attributes_final_height;
    // For NES this is post-alignment AND packed
    size_t map_attributes_packed_width;
    size_t map_attributes_packed_height;


    size_t colors_per_pal;  // Number of colors per palette (ex: CGB has 4 colors per palette x 8 palettes total)
    size_t total_color_count; // Total number of colors across all palettes (palette_count x colors_per_pal)
    unsigned char* palette; //palette colors in RGBA (1 color == 4 bytes)

private:
    bool zero_palette = false;

public:
    unsigned char GetGBColor(int x, int y)
    {
        return data[w * y + x] % colors_per_pal;
    }


    // This needs separate tile_w and tile_h params since
    // MSX tile extraction uses it to pull out the 4 sub-tiles
    bool ExtractGBTile(int x, int y, int extract_tile_w, int extract_tile_h, Tile& tile, int buffer_offset)
    {
        // Set the palette to 0 when pals are not stored in tiles to allow tiles to be equal even when their palettes are different
        tile.pal = zero_palette ? 0 : data[w * y + x] >> 2;

        bool all_zero = true;
        for(int j = 0; j < extract_tile_h; ++ j)
        {
            for(int i = 0; i < extract_tile_w; ++i)
            {
                unsigned char color_idx = GetGBColor(x + i, y + j);
                tile.data[(j * extract_tile_w) + i + buffer_offset] = color_idx;
                all_zero = all_zero && (color_idx == 0);
            }
        }
        return !all_zero;
    }

    bool ExtractTile_MSX16x16(int x, int y, Tile& tile)
    {
        // MSX 16x16 sprite tiles are composed of four 8x8 tiles in this order UL, LL, UR, LR
        bool UL_notempty, LL_notempty, UR_notempty, LR_notempty;

        // Call these separately since otherwise some get optimized out during
        // runtime if any single one before it returns false
        UL_notempty = ExtractGBTile(x,     y,     8, 8, tile, 0);
        LL_notempty = ExtractGBTile(x,     y + 8, 8, 8, tile, ((8 *8) * 1));
        UR_notempty = ExtractGBTile(x + 8, y,     8, 8, tile, ((8 *8) * 2));
        LR_notempty = ExtractGBTile(x + 8, y + 8, 8, 8, tile, ((8 *8) * 3));
        return (UL_notempty || LL_notempty || UR_notempty || LR_notempty);
    }

    bool ExtractTile(int x, int y, Tile& tile, int sprite_mode, bool export_as_map, bool use_map_attributes)
    {
        // Set the palette to 0 when pals are not stored in tiles to allow tiles to be equal even when their palettes are different
        zero_palette = !(export_as_map && !use_map_attributes);

        if (sprite_mode == SPR_16x16_MSX)
            return ExtractTile_MSX16x16(x, y, tile);
        else
            return ExtractGBTile(x, y, tile_w, tile_h, tile, 0); // No buffer offset for normal tile extraction
    }

    void CopySettingsTo(PNGImage& destImage) {
        destImage.colors_per_pal = colors_per_pal;
        destImage.tile_w = tile_w;
        destImage.tile_h = tile_h;

        destImage.map_attributes_divide_w = map_attributes_divide_w;
        destImage.map_attributes_divide_h = map_attributes_divide_h;

        destImage.map_attributes_final_width = map_attributes_final_width;
        destImage.map_attributes_final_height = map_attributes_final_height;

        destImage.map_attributes_packed_width = map_attributes_packed_width;
        destImage.map_attributes_packed_height = map_attributes_packed_height;
    }
};

#endif
