/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
*/
#ifndef __FSDITHER_H__
#define __FSDITHER_H__

/* The following 5 arrays are used in performing floyd-steinberg
 * error diffusion dithering. The range array allows the quick
 * bounds checking of pixel values. The 4 error arrays contain
 * the error computations for the east, south-east, south and
 * south-west pixels surrounding the current pixel respectively.
 */

//short
unsigned char
	range_array[] = {
/*
 1 2 3 4 5 6 7 8 9 0
*/
 0,0,0,0,0,0,0,0,0,0,   // L20
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,1,2,3, // L45 (+25) 250 - 260-4=256
 4,5,6,7,8,9,10,11,12,13,
 14,15,16,17,18,19,20,21,22,23,
 24,25,26,27,28,29,30,31,32,33,
 34,35,36,37,38,39,40,41,42,43,
 44,45,46,47,48,49,50,51,52,53,
 54,55,56,57,58,59,60,61,62,63,
 64,65,66,67,68,69,70,71,72,73,
 74,75,76,77,78,79,80,81,82,83,
 84,85,86,87,88,89,90,91,92,93,
 94,95,96,97,98,99,100,101,102,103,
 104,105,106,107,108,109,110,111,112,113,
 114,115,116,117,118,119,120,121,122,123,
 124,125,126,127,128,129,130,131,132,133,
 134,135,136,137,138,139,140,141,142,143,
 144,145,146,147,148,149,150,151,152,153,
 154,155,156,157,158,159,160,161,162,163,
 164,165,166,167,168,169,170,171,172,173,
 174,175,176,177,178,179,180,181,182,183,
 184,185,186,187,188,189,190,191,192,193,
 194,195,196,197,198,199,200,201,202,203,
 204,205,206,207,208,209,210,211,212,213,
 214,215,216,217,218,219,220,221,222,223,
 224,225,226,227,228,229,230,231,232,233,
 234,235,236,237,238,239,240,241,242,243,
 244,245,246,247,248,249,250,251,252,253,
 254,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,         			// L122 : 122-20=102
						// 102*10-5 = 1015
};

short floyd_steinberg_error1[] = {
 -223,-223,-222,-222,-221,-221,-220,-220,-220,-219,
 -219,-218,-218,-217,-217,-217,-216,-216,-215,-215,
 -214,-214,-213,-213,-213,-212,-212,-211,-211,-210,
 -210,-210,-209,-209,-208,-208,-207,-207,-206,-206,
 -206,-205,-205,-204,-204,-203,-203,-203,-202,-202,
 -201,-201,-200,-200,-199,-199,-199,-198,-198,-197,
 -197,-196,-196,-196,-195,-195,-194,-194,-193,-193,
 -192,-192,-192,-191,-191,-190,-190,-189,-189,-189,
 -188,-188,-187,-187,-186,-186,-185,-185,-185,-184,
 -184,-183,-183,-182,-182,-182,-181,-181,-180,-180,
 -179,-179,-178,-178,-178,-177,-177,-176,-176,-175,
 -175,-175,-174,-174,-173,-173,-172,-172,-171,-171,
 -171,-170,-170,-169,-169,-168,-168,-168,-167,-167,
 -166,-166,-165,-165,-164,-164,-164,-163,-163,-162,
 -162,-161,-161,-161,-160,-160,-159,-159,-158,-158,
 -157,-157,-157,-156,-156,-155,-155,-154,-154,-154,
 -153,-153,-152,-152,-151,-151,-150,-150,-150,-149,
 -149,-148,-148,-147,-147,-147,-146,-146,-145,-145,
 -144,-144,-143,-143,-143,-142,-142,-141,-141,-140,
 -140,-140,-139,-139,-138,-138,-137,-137,-136,-136,
 -136,-135,-135,-134,-134,-133,-133,-133,-132,-132,
 -131,-131,-130,-130,-129,-129,-129,-128,-128,-127,
 -127,-126,-126,-126,-125,-125,-124,-124,-123,-123,
 -122,-122,-122,-121,-121,-120,-120,-119,-119,-119,
 -118,-118,-117,-117,-116,-116,-115,-115,-115,-114,
 -114,-113,-113,-112,-112,-112,-111,-111,-110,-110,
 -109,-109,-108,-108,-108,-107,-107,-106,-106,-105,
 -105,-105,-104,-104,-103,-103,-102,-102,-101,-101,
 -101,-100,-100,-99,-99,-98,-98,-98,-97,-97,
 -96,-96,-95,-95,-94,-94,-94,-93,-93,-92,
 -92,-91,-91,-91,-90,-90,-89,-89,-88,-88,
 -87,-87,-87,-86,-86,-85,-85,-84,-84,-84,
 -83,-83,-82,-82,-81,-81,-80,-80,-80,-79,
 -79,-78,-78,-77,-77,-77,-76,-76,-75,-75,
 -74,-74,-73,-73,-73,-72,-72,-71,-71,-70,
 -70,-70,-69,-69,-68,-68,-67,-67,-66,-66,
 -66,-65,-65,-64,-64,-63,-63,-63,-62,-62,
 -61,-61,-60,-60,-59,-59,-59,-58,-58,-57,
 -57,-56,-56,-56,-55,-55,-54,-54,-53,-53,
 -52,-52,-52,-51,-51,-50,-50,-49,-49,-49,
 -48,-48,-47,-47,-46,-46,-45,-45,-45,-44,
 -44,-43,-43,-42,-42,-42,-41,-41,-40,-40,
 -39,-39,-38,-38,-38,-37,-37,-36,-36,-35,
 -35,-35,-34,-34,-33,-33,-32,-32,-31,-31,
 -31,-30,-30,-29,-29,-28,-28,-28,-27,-27,
 -26,-26,-25,-25,-24,-24,-24,-23,-23,-22,
 -22,-21,-21,-21,-20,-20,-19,-19,-18,-18,
 -17,-17,-17,-16,-16,-15,-15,-14,-14,-14,
 -13,-13,-12,-12,-11,-11,-10,-10,-10,-9,
 -9,-8,-8,-7,-7,-7,-6,-6,-5,-5,
 -4,-4,-3,-3,-3,-2,-2,-1,-1,
			    0,
 0,0,0,0,1,1,2,2,3,3,
 3,4,4,5,5,6,6,7,7,7,
 8,8,9,9,10,10,10,11,11,12,
 12,13,13,14,14,14,15,15,16,16,
 17,17,17,18,18,19,19,20,20,21,
 21,21,22,22,23,23,24,24,24,25,
 25,26,26,27,27,28,28,28,29,29,
 30,30,31,31,31,32,32,33,33,34,
 34,35,35,35,36,36,37,37,38,38,
 38,39,39,40,40,41,41,42,42,42,
 43,43,44,44,45,45,45,46,46,47,
 47,48,48,49,49,49,50,50,51,51,
 52,52,52,53,53,54,54,55,55,56,
 56,56,57,57,58,58,59,59,59,60,
 60,61,61,62,62,63,63,63,64,64,
 65,65,66,66,66,67,67,68,68,69,
 69,70,70,70,71,71,72,72,73,73,
 73,74,74,75,75,76,76,77,77,77,
 78,78,79,79,80,80,80,81,81,82,
 82,83,83,84,84,84,85,85,86,86,
 87,87,87,88,88,89,89,90,90,91,
 91,91,92,92,93,93,94,94,94,95,
 95,96,96,97,97,98,98,98,99,99,
 100,100,101,101,101,102,102,103,103,104,
 104,105,105,105,106,106,107,107,108,108,
 108,109,109,110,110,111,111,112,112,112,
 113,113,114,114,115,115,115,116,116,117,
 117,118,118,119,119,119,120,120,121,121,
 122,122,122,123,123,124,124,125,125,126,
 126,126,127,127,128,128,129,129,129,130,
 130,131,131,132,132,133,133,133,134,134,
 135,135,136,136,136,137,137,138,138,139,
 139,140,140,140,141,141,142,142,143,143,
 143,144,144,145,145,146,146,147,147,147,
 148,148,149,149,150,150,150,151,151,152,
 152,153,153,154,154,154,155,155,156,156,
 157,157,157,158,158,159,159,160,160,161,
 161,161,162,162,163,163,164,164,164,165,
 165,166,166,167,167,168,168,168,169,169,
 170,170,171,171,171,172,172,173,173,174,
 174,175,175,175,176,176,177,177,178,178,
 178,179,179,180,180,181,181,182,182,182,
 183,183,184,184,185,185,185,186,186,187,
 187,188,188,189,189,189,190,190,191,191,
 192,192,192,193,193,194,194,195,195,196,
 196,196,197,197,198,198,199,199,199,200,
 200,201,201,202,202,203,203,203,204,204,
 205,205,206,206,206,207,207,208,208,209,
 209,210,210,210,211,211,212,212,213,213,
 213,214,214,215,215,216,216,217,217,217,
 218,218,219,219,220,220,220,221,221,222,
 222,223,223,224,224,
};

short floyd_steinberg_error2[] = {
 -95,-95,-95,-95,-95,-94,-94,-94,-94,-94,
 -93,-93,-93,-93,-93,-93,-92,-92,-92,-92,
 -92,-91,-91,-91,-91,-91,-90,-90,-90,-90,
 -90,-90,-89,-89,-89,-89,-89,-88,-88,-88,
 -88,-88,-87,-87,-87,-87,-87,-87,-86,-86,
 -86,-86,-86,-85,-85,-85,-85,-85,-84,-84,
 -84,-84,-84,-84,-83,-83,-83,-83,-83,-82,
 -82,-82,-82,-82,-81,-81,-81,-81,-81,-81,
 -80,-80,-80,-80,-80,-79,-79,-79,-79,-79,
 -78,-78,-78,-78,-78,-78,-77,-77,-77,-77,
 -77,-76,-76,-76,-76,-76,-75,-75,-75,-75,
 -75,-75,-74,-74,-74,-74,-74,-73,-73,-73,
 -73,-73,-72,-72,-72,-72,-72,-72,-71,-71,
 -71,-71,-71,-70,-70,-70,-70,-70,-69,-69,
 -69,-69,-69,-69,-68,-68,-68,-68,-68,-67,
 -67,-67,-67,-67,-66,-66,-66,-66,-66,-66,
 -65,-65,-65,-65,-65,-64,-64,-64,-64,-64,
 -63,-63,-63,-63,-63,-63,-62,-62,-62,-62,
 -62,-61,-61,-61,-61,-61,-60,-60,-60,-60,
 -60,-60,-59,-59,-59,-59,-59,-58,-58,-58,
 -58,-58,-57,-57,-57,-57,-57,-57,-56,-56,
 -56,-56,-56,-55,-55,-55,-55,-55,-54,-54,
 -54,-54,-54,-54,-53,-53,-53,-53,-53,-52,
 -52,-52,-52,-52,-51,-51,-51,-51,-51,-51,
 -50,-50,-50,-50,-50,-49,-49,-49,-49,-49,
 -48,-48,-48,-48,-48,-48,-47,-47,-47,-47,
 -47,-46,-46,-46,-46,-46,-45,-45,-45,-45,
 -45,-45,-44,-44,-44,-44,-44,-43,-43,-43,
 -43,-43,-42,-42,-42,-42,-42,-42,-41,-41,
 -41,-41,-41,-40,-40,-40,-40,-40,-39,-39,
 -39,-39,-39,-39,-38,-38,-38,-38,-38,-37,
 -37,-37,-37,-37,-36,-36,-36,-36,-36,-36,
 -35,-35,-35,-35,-35,-34,-34,-34,-34,-34,
 -33,-33,-33,-33,-33,-33,-32,-32,-32,-32,
 -32,-31,-31,-31,-31,-31,-30,-30,-30,-30,
 -30,-30,-29,-29,-29,-29,-29,-28,-28,-28,
 -28,-28,-27,-27,-27,-27,-27,-27,-26,-26,
 -26,-26,-26,-25,-25,-25,-25,-25,-24,-24,
 -24,-24,-24,-24,-23,-23,-23,-23,-23,-22,
 -22,-22,-22,-22,-21,-21,-21,-21,-21,-21,
 -20,-20,-20,-20,-20,-19,-19,-19,-19,-19,
 -18,-18,-18,-18,-18,-18,-17,-17,-17,-17,
 -17,-16,-16,-16,-16,-16,-15,-15,-15,-15,
 -15,-15,-14,-14,-14,-14,-14,-13,-13,-13,
 -13,-13,-12,-12,-12,-12,-12,-12,-11,-11,
 -11,-11,-11,-10,-10,-10,-10,-10,-9,-9,
 -9,-9,-9,-9,-8,-8,-8,-8,-8,-7,
 -7,-7,-7,-7,-6,-6,-6,-6,-6,-6,
 -5,-5,-5,-5,-5,-4,-4,-4,-4,-4,
 -3,-3,-3,-3,-3,-3,-2,-2,-2,-2,
 -2,-1,-1,-1,-1,-1,
		   0,0,0,0,
 0,0,0,0,0,0,0,1,1,1,
 1,1,2,2,2,2,2,3,3,3,
 3,3,3,4,4,4,4,4,5,5,
 5,5,5,6,6,6,6,6,6,7,
 7,7,7,7,8,8,8,8,8,9,
 9,9,9,9,9,10,10,10,10,10,
 11,11,11,11,11,12,12,12,12,12,
 12,13,13,13,13,13,14,14,14,14,
 14,15,15,15,15,15,15,16,16,16,
 16,16,17,17,17,17,17,18,18,18,
 18,18,18,19,19,19,19,19,20,20,
 20,20,20,21,21,21,21,21,21,22,
 22,22,22,22,23,23,23,23,23,24,
 24,24,24,24,24,25,25,25,25,25,
 26,26,26,26,26,27,27,27,27,27,
 27,28,28,28,28,28,29,29,29,29,
 29,30,30,30,30,30,30,31,31,31,
 31,31,32,32,32,32,32,33,33,33,
 33,33,33,34,34,34,34,34,35,35,
 35,35,35,36,36,36,36,36,36,37,
 37,37,37,37,38,38,38,38,38,39,
 39,39,39,39,39,40,40,40,40,40,
 41,41,41,41,41,42,42,42,42,42,
 42,43,43,43,43,43,44,44,44,44,
 44,45,45,45,45,45,45,46,46,46,
 46,46,47,47,47,47,47,48,48,48,
 48,48,48,49,49,49,49,49,50,50,
 50,50,50,51,51,51,51,51,51,52,
 52,52,52,52,53,53,53,53,53,54,
 54,54,54,54,54,55,55,55,55,55,
 56,56,56,56,56,57,57,57,57,57,
 57,58,58,58,58,58,59,59,59,59,
 59,60,60,60,60,60,60,61,61,61,
 61,61,62,62,62,62,62,63,63,63,
 63,63,63,64,64,64,64,64,65,65,
 65,65,65,66,66,66,66,66,66,67,
 67,67,67,67,68,68,68,68,68,69,
 69,69,69,69,69,70,70,70,70,70,
 71,71,71,71,71,72,72,72,72,72,
 72,73,73,73,73,73,74,74,74,74,
 74,75,75,75,75,75,75,76,76,76,
 76,76,77,77,77,77,77,78,78,78,
 78,78,78,79,79,79,79,79,80,80,
 80,80,80,81,81,81,81,81,81,82,
 82,82,82,82,83,83,83,83,83,84,
 84,84,84,84,84,85,85,85,85,85,
 86,86,86,86,86,87,87,87,87,87,
 87,88,88,88,88,88,89,89,89,89,
 89,90,90,90,90,90,90,91,91,91,
 91,91,92,92,92,92,92,93,93,93,
 93,93,93,94,94,94,94,94,95,95,
 95,95,95,96,96,
};

short floyd_steinberg_error3[] = {
 -159,-159,-159,-158,-158,-158,-157,-157,-157,-156,
 -156,-156,-155,-155,-155,-155,-154,-154,-154,-153,
 -153,-153,-152,-152,-152,-151,-151,-151,-150,-150,
 -150,-150,-149,-149,-149,-148,-148,-148,-147,-147,
 -147,-146,-146,-146,-145,-145,-145,-145,-144,-144,
 -144,-143,-143,-143,-142,-142,-142,-141,-141,-141,
 -140,-140,-140,-140,-139,-139,-139,-138,-138,-138,
 -137,-137,-137,-136,-136,-136,-135,-135,-135,-135,
 -134,-134,-134,-133,-133,-133,-132,-132,-132,-131,
 -131,-131,-130,-130,-130,-130,-129,-129,-129,-128,
 -128,-128,-127,-127,-127,-126,-126,-126,-125,-125,
 -125,-125,-124,-124,-124,-123,-123,-123,-122,-122,
 -122,-121,-121,-121,-120,-120,-120,-120,-119,-119,
 -119,-118,-118,-118,-117,-117,-117,-116,-116,-116,
 -115,-115,-115,-115,-114,-114,-114,-113,-113,-113,
 -112,-112,-112,-111,-111,-111,-110,-110,-110,-110,
 -109,-109,-109,-108,-108,-108,-107,-107,-107,-106,
 -106,-106,-105,-105,-105,-105,-104,-104,-104,-103,
 -103,-103,-102,-102,-102,-101,-101,-101,-100,-100,
 -100,-100,-99,-99,-99,-98,-98,-98,-97,-97,
 -97,-96,-96,-96,-95,-95,-95,-95,-94,-94,
 -94,-93,-93,-93,-92,-92,-92,-91,-91,-91,
 -90,-90,-90,-90,-89,-89,-89,-88,-88,-88,
 -87,-87,-87,-86,-86,-86,-85,-85,-85,-85,
 -84,-84,-84,-83,-83,-83,-82,-82,-82,-81,
 -81,-81,-80,-80,-80,-80,-79,-79,-79,-78,
 -78,-78,-77,-77,-77,-76,-76,-76,-75,-75,
 -75,-75,-74,-74,-74,-73,-73,-73,-72,-72,
 -72,-71,-71,-71,-70,-70,-70,-70,-69,-69,
 -69,-68,-68,-68,-67,-67,-67,-66,-66,-66,
 -65,-65,-65,-65,-64,-64,-64,-63,-63,-63,
 -62,-62,-62,-61,-61,-61,-60,-60,-60,-60,
 -59,-59,-59,-58,-58,-58,-57,-57,-57,-56,
 -56,-56,-55,-55,-55,-55,-54,-54,-54,-53,
 -53,-53,-52,-52,-52,-51,-51,-51,-50,-50,
 -50,-50,-49,-49,-49,-48,-48,-48,-47,-47,
 -47,-46,-46,-46,-45,-45,-45,-45,-44,-44,
 -44,-43,-43,-43,-42,-42,-42,-41,-41,-41,
 -40,-40,-40,-40,-39,-39,-39,-38,-38,-38,
 -37,-37,-37,-36,-36,-36,-35,-35,-35,-35,
 -34,-34,-34,-33,-33,-33,-32,-32,-32,-31,
 -31,-31,-30,-30,-30,-30,-29,-29,-29,-28,
 -28,-28,-27,-27,-27,-26,-26,-26,-25,-25,
 -25,-25,-24,-24,-24,-23,-23,-23,-22,-22,
 -22,-21,-21,-21,-20,-20,-20,-20,-19,-19,
 -19,-18,-18,-18,-17,-17,-17,-16,-16,-16,
 -15,-15,-15,-15,-14,-14,-14,-13,-13,-13,
 -12,-12,-12,-11,-11,-11,-10,-10,-10,-10,
 -9,-9,-9,-8,-8,-8,-7,-7,-7,-6,
 -6,-6,-5,-5,-5,-5,-4,-4,-4,-3,
 -3,-3,-2,-2,-2,-1,-1,-1,
			 0,0,
 0,0,0,0,0,1,1,1,2,2,
 2,3,3,3,4,4,4,5,5,5,
 5,6,6,6,7,7,7,8,8,8,
 9,9,9,10,10,10,10,11,11,11,
 12,12,12,13,13,13,14,14,14,15,
 15,15,15,16,16,16,17,17,17,18,
 18,18,19,19,19,20,20,20,20,21,
 21,21,22,22,22,23,23,23,24,24,
 24,25,25,25,25,26,26,26,27,27,
 27,28,28,28,29,29,29,30,30,30,
 30,31,31,31,32,32,32,33,33,33,
 34,34,34,35,35,35,35,36,36,36,
 37,37,37,38,38,38,39,39,39,40,
 40,40,40,41,41,41,42,42,42,43,
 43,43,44,44,44,45,45,45,45,46,
 46,46,47,47,47,48,48,48,49,49,
 49,50,50,50,50,51,51,51,52,52,
 52,53,53,53,54,54,54,55,55,55,
 55,56,56,56,57,57,57,58,58,58,
 59,59,59,60,60,60,60,61,61,61,
 62,62,62,63,63,63,64,64,64,65,
 65,65,65,66,66,66,67,67,67,68,
 68,68,69,69,69,70,70,70,70,71,
 71,71,72,72,72,73,73,73,74,74,
 74,75,75,75,75,76,76,76,77,77,
 77,78,78,78,79,79,79,80,80,80,
 80,81,81,81,82,82,82,83,83,83,
 84,84,84,85,85,85,85,86,86,86,
 87,87,87,88,88,88,89,89,89,90,
 90,90,90,91,91,91,92,92,92,93,
 93,93,94,94,94,95,95,95,95,96,
 96,96,97,97,97,98,98,98,99,99,
 99,100,100,100,100,101,101,101,102,102,
 102,103,103,103,104,104,104,105,105,105,
 105,106,106,106,107,107,107,108,108,108,
 109,109,109,110,110,110,110,111,111,111,
 112,112,112,113,113,113,114,114,114,115,
 115,115,115,116,116,116,117,117,117,118,
 118,118,119,119,119,120,120,120,120,121,
 121,121,122,122,122,123,123,123,124,124,
 124,125,125,125,125,126,126,126,127,127,
 127,128,128,128,129,129,129,130,130,130,
 130,131,131,131,132,132,132,133,133,133,
 134,134,134,135,135,135,135,136,136,136,
 137,137,137,138,138,138,139,139,139,140,
 140,140,140,141,141,141,142,142,142,143,
 143,143,144,144,144,145,145,145,145,146,
 146,146,147,147,147,148,148,148,149,149,
 149,150,150,150,150,151,151,151,152,152,
 152,153,153,153,154,154,154,155,155,155,
 155,156,156,156,157,157,157,158,158,158,
 159,159,159,160,160,
};

short floyd_steinberg_error4[] = {
 -34,-33,-33,-33,-33,-33,-34,-33,-32,-33,
 -33,-33,-33,-33,-32,-31,-33,-32,-32,-32,
 -32,-32,-33,-32,-31,-32,-32,-32,-32,-32,
 -31,-30,-32,-31,-31,-31,-31,-31,-32,-31,
 -30,-31,-31,-31,-31,-31,-30,-29,-31,-30,
 -30,-30,-30,-30,-31,-30,-29,-30,-30,-30,
 -30,-30,-29,-28,-30,-29,-29,-29,-29,-29,
 -30,-29,-28,-29,-29,-29,-29,-29,-28,-27,
 -29,-28,-28,-28,-28,-28,-29,-28,-27,-28,
 -28,-28,-28,-28,-27,-26,-28,-27,-27,-27,
 -27,-27,-28,-27,-26,-27,-27,-27,-27,-27,
 -26,-25,-27,-26,-26,-26,-26,-26,-27,-26,
 -25,-26,-26,-26,-26,-26,-25,-24,-26,-25,
 -25,-25,-25,-25,-26,-25,-24,-25,-25,-25,
 -25,-25,-24,-23,-25,-24,-24,-24,-24,-24,
 -25,-24,-23,-24,-24,-24,-24,-24,-23,-22,
 -24,-23,-23,-23,-23,-23,-24,-23,-22,-23,
 -23,-23,-23,-23,-22,-21,-23,-22,-22,-22,
 -22,-22,-23,-22,-21,-22,-22,-22,-22,-22,
 -21,-20,-22,-21,-21,-21,-21,-21,-22,-21,
 -20,-21,-21,-21,-21,-21,-20,-19,-21,-20,
 -20,-20,-20,-20,-21,-20,-19,-20,-20,-20,
 -20,-20,-19,-18,-20,-19,-19,-19,-19,-19,
 -20,-19,-18,-19,-19,-19,-19,-19,-18,-17,
 -19,-18,-18,-18,-18,-18,-19,-18,-17,-18,
 -18,-18,-18,-18,-17,-16,-18,-17,-17,-17,
 -17,-17,-18,-17,-16,-17,-17,-17,-17,-17,
 -16,-15,-17,-16,-16,-16,-16,-16,-17,-16,
 -15,-16,-16,-16,-16,-16,-15,-14,-16,-15,
 -15,-15,-15,-15,-16,-15,-14,-15,-15,-15,
 -15,-15,-14,-13,-15,-14,-14,-14,-14,-14,
 -15,-14,-13,-14,-14,-14,-14,-14,-13,-12,
 -14,-13,-13,-13,-13,-13,-14,-13,-12,-13,
 -13,-13,-13,-13,-12,-11,-13,-12,-12,-12,
 -12,-12,-13,-12,-11,-12,-12,-12,-12,-12,
 -11,-10,-12,-11,-11,-11,-11,-11,-12,-11,
 -10,-11,-11,-11,-11,-11,-10,-9,-11,-10,
 -10,-10,-10,-10,-11,-10,-9,-10,-10,-10,
 -10,-10,-9,-8,-10,-9,-9,-9,-9,-9,
 -10,-9,-8,-9,-9,-9,-9,-9,-8,-7,
 -9,-8,-8,-8,-8,-8,-9,-8,-7,-8,
 -8,-8,-8,-8,-7,-6,-8,-7,-7,-7,
 -7,-7,-8,-7,-6,-7,-7,-7,-7,-7,
 -6,-5,-7,-6,-6,-6,-6,-6,-7,-6,
 -5,-6,-6,-6,-6,-6,-5,-4,-6,-5,
 -5,-5,-5,-5,-6,-5,-4,-5,-5,-5,
 -5,-5,-4,-3,-5,-4,-4,-4,-4,-4,
 -5,-4,-3,-4,-4,-4,-4,-4,-3,-2,
 -4,-3,-3,-3,-3,-3,-4,-3,-2,-3,
 -3,-3,-3,-3,-2,-1,-3,-2,-2,-2,
 -2,-2,-3,-2,-1,-2,-2,-2,-2,-2,
 -1,
    0,1,2,2,2,2,2,1,2,
 3,2,2,2,2,2,3,1,2,3,
 3,3,3,3,2,3,4,3,3,3,
 3,3,4,2,3,4,4,4,4,4,
 3,4,5,4,4,4,4,4,5,3,
 4,5,5,5,5,5,4,5,6,5,
 5,5,5,5,6,4,5,6,6,6,
 6,6,5,6,7,6,6,6,6,6,
 7,5,6,7,7,7,7,7,6,7,
 8,7,7,7,7,7,8,6,7,8,
 8,8,8,8,7,8,9,8,8,8,
 8,8,9,7,8,9,9,9,9,9,
 8,9,10,9,9,9,9,9,10,8,
 9,10,10,10,10,10,9,10,11,10,
 10,10,10,10,11,9,10,11,11,11,
 11,11,10,11,12,11,11,11,11,11,
 12,10,11,12,12,12,12,12,11,12,
 13,12,12,12,12,12,13,11,12,13,
 13,13,13,13,12,13,14,13,13,13,
 13,13,14,12,13,14,14,14,14,14,
 13,14,15,14,14,14,14,14,15,13,
 14,15,15,15,15,15,14,15,16,15,
 15,15,15,15,16,14,15,16,16,16,
 16,16,15,16,17,16,16,16,16,16,
 17,15,16,17,17,17,17,17,16,17,
 18,17,17,17,17,17,18,16,17,18,
 18,18,18,18,17,18,19,18,18,18,
 18,18,19,17,18,19,19,19,19,19,
 18,19,20,19,19,19,19,19,20,18,
 19,20,20,20,20,20,19,20,21,20,
 20,20,20,20,21,19,20,21,21,21,
 21,21,20,21,22,21,21,21,21,21,
 22,20,21,22,22,22,22,22,21,22,
 23,22,22,22,22,22,23,21,22,23,
 23,23,23,23,22,23,24,23,23,23,
 23,23,24,22,23,24,24,24,24,24,
 23,24,25,24,24,24,24,24,25,23,
 24,25,25,25,25,25,24,25,26,25,
 25,25,25,25,26,24,25,26,26,26,
 26,26,25,26,27,26,26,26,26,26,
 27,25,26,27,27,27,27,27,26,27,
 28,27,27,27,27,27,28,26,27,28,
 28,28,28,28,27,28,29,28,28,28,
 28,28,29,27,28,29,29,29,29,29,
 28,29,30,29,29,29,29,29,30,28,
 29,30,30,30,30,30,29,30,31,30,
 30,30,30,30,31,29,30,31,31,31,
 31,31,30,31,32,31,31,31,31,31,
 32,30,31,32,32,32,32,32,31,32,
 33,32,32,32,32,32,33,31,32,33,
 33,33,33,33,32,33,34,33,33,33,
 33,33,34,32,33,
};

#endif /* __FSDITHER_H__ */
