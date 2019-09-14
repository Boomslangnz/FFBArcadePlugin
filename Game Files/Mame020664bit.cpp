/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include <tchar.h>
#include "Mame020664bit.h"
#include "math.h"

static int sanfran64(int ffsan64) {
	switch (ffsan64) {

	case 0xFF:
		return 232;
	case 0xFE:
		return 231;
	case 0xFD:
		return 230;
	case 0xFC:
		return 229;
	case 0xFB:
		return 228;
	case 0xFA:
		return 227;
	case 0xF9:
		return 226;
	case 0xF8:
		return 225;
	case 0xF7:
		return 224;
	case 0xF6:
		return 223;
	case 0xF5:
		return 222;
	case 0xF4:
		return 221;
	case 0xF3:
		return 220;
	case 0xF2:
		return 219;
	case 0xF1:
		return 218;
	case 0xEF:
		return 217;
	case 0xEE:
		return 216;
	case 0xED:
		return 215;
	case 0xEC:
		return 214;
	case 0xEB:
		return 213;
	case 0xEA:
		return 212;
	case 0xE9:
		return 211;
	case 0xE8:
		return 210;
	case 0xE7:
		return 209;
	case 0xE6:
		return 208;
	case 0xE5:
		return 207;
	case 0xE4:
		return 206;
	case 0xE3:
		return 205;
	case 0xE2:
		return 204;
	case 0xE1:
		return 203;
	case 0xDF:
		return 202;
	case 0xDE:
		return 201;
	case 0xDD:
		return 200;
	case 0xDC:
		return 199;
	case 0xDB:
		return 198;
	case 0xDA:
		return 197;
	case 0xD9:
		return 196;
	case 0xD8:
		return 195;
	case 0xD7:
		return 194;
	case 0xD6:
		return 193;
	case 0xD5:
		return 192;
	case 0xD4:
		return 191;
	case 0xD3:
		return 190;
	case 0xD2:
		return 189;
	case 0xD1:
		return 188;
	case 0xCF:
		return 187;
	case 0xCE:
		return 186;
	case 0xCD:
		return 185;
	case 0xCC:
		return 184;
	case 0xCB:
		return 183;
	case 0xCA:
		return 182;
	case 0xC9:
		return 181;
	case 0xC8:
		return 180;
	case 0xC7:
		return 179;
	case 0xC6:
		return 178;
	case 0xC5:
		return 177;
	case 0xC4:
		return 176;
	case 0xC3:
		return 175;
	case 0xC2:
		return 174;
	case 0xC1:
		return 173;
	case 0xBF:
		return 172;
	case 0xBE:
		return 171;
	case 0xBD:
		return 170;
	case 0xBC:
		return 169;
	case 0xBB:
		return 168;
	case 0xBA:
		return 167;
	case 0xB9:
		return 166;
	case 0xB8:
		return 165;
	case 0xB7:
		return 164;
	case 0xB6:
		return 163;
	case 0xB5:
		return 162;
	case 0xB4:
		return 161;
	case 0xB3:
		return 160;
	case 0xB2:
		return 159;
	case 0xB1:
		return 158;
	case 0xAF:
		return 157;
	case 0xAE:
		return 156;
	case 0xAD:
		return 155;
	case 0xAC:
		return 154;
	case 0xAB:
		return 153;
	case 0xAA:
		return 152;
	case 0xA9:
		return 151;
	case 0xA8:
		return 150;
	case 0xA7:
		return 149;
	case 0xA6:
		return 148;
	case 0xA5:
		return 147;
	case 0xA4:
		return 146;
	case 0xA3:
		return 145;
	case 0xA2:
		return 144;
	case 0xA1:
		return 143;
	case 0x9F:
		return 142;
	case 0x9E:
		return 141;
	case 0x9D:
		return 140;
	case 0x9C:
		return 139;
	case 0x9B:
		return 138;
	case 0x9A:
		return 137;
	case 0x99:
		return 136;
	case 0x98:
		return 135;
	case 0x97:
		return 134;
	case 0x96:
		return 133;
	case 0x95:
		return 132;
	case 0x94:
		return 131;
	case 0x93:
		return 130;
	case 0x92:
		return 129;
	case 0x91:
		return 128;
	case 0x8F:
		return 127;
	case 0x8E:
		return 126;
	case 0x8D:
		return 125;
	case 0x8C:
		return 124;
	case 0x8B:
		return 123;
	case 0x8A:
		return 122;
	case 0x89:
		return 121;
	case 0x88:
		return 120;
	case 0x87:
		return 119;
	case 0x86:
		return 118;
	case 0x85:
		return 117;
	case 0x84:
		return 116;
	case 0x83:
		return 115;
	case 0x82:
		return 114;
	case 0x81:
		return 113;

	case 0x7F:
		return 112;
	case 0x7E:
		return 111;
	case 0x7D:
		return 110;
	case 0x7C:
		return 109;
	case 0x7B:
		return 108;
	case 0x7A:
		return 107;
	case 0x79:
		return 106;
	case 0x78:
		return 105;
	case 0x77:
		return 104;
	case 0x76:
		return 103;
	case 0x75:
		return 102;
	case 0x74:
		return 101;
	case 0x73:
		return 100;
	case 0x72:
		return 99;
	case 0x71:
		return 98;
	case 0x6F:
		return 97;
	case 0x6E:
		return 96;
	case 0x6D:
		return 95;
	case 0x6C:
		return 94;
	case 0x6B:
		return 93;
	case 0x6A:
		return 92;
	case 0x69:
		return 91;
	case 0x68:
		return 90;
	case 0x67:
		return 89;
	case 0x66:
		return 88;
	case 0x65:
		return 87;
	case 0x64:
		return 86;
	case 0x63:
		return 85;
	case 0x62:
		return 84;
	case 0x61:
		return 83;
	case 0x5F:
		return 82;
	case 0x5E:
		return 81;
	case 0x5D:
		return 80;
	case 0x5C:
		return 79;
	case 0x5B:
		return 78;
	case 0x5A:
		return 77;
	case 0x59:
		return 76;
	case 0x58:
		return 75;
	case 0x57:
		return 74;
	case 0x56:
		return 73;
	case 0x55:
		return 72;
	case 0x54:
		return 71;
	case 0x53:
		return 70;
	case 0x52:
		return 69;
	case 0x51:
		return 68;
	case 0x4F:
		return 67;
	case 0x4E:
		return 66;
	case 0x4D:
		return 65;
	case 0x4C:
		return 64;
	case 0x4B:
		return 63;
	case 0x4A:
		return 62;
	case 0x49:
		return 61;
	case 0x48:
		return 60;
	case 0x47:
		return 59;
	case 0x46:
		return 58;
	case 0x45:
		return 57;
	case 0x44:
		return 56;
	case 0x43:
		return 55;
	case 0x42:
		return 54;
	case 0x41:
		return 53;
	case 0x3F:
		return 52;
	case 0x3E:
		return 51;
	case 0x3D:
		return 50;
	case 0x3C:
		return 49;
	case 0x3B:
		return 48;
	case 0x3A:
		return 47;
	case 0x39:
		return 46;
	case 0x38:
		return 45;
	case 0x37:
		return 44;
	case 0x36:
		return 43;
	case 0x35:
		return 42;
	case 0x34:
		return 41;
	case 0x33:
		return 40;
	case 0x32:
		return 39;
	case 0x31:
		return 38;
	case 0x29:
		return 37;
	case 0x28:
		return 36;
	case 0x27:
		return 35;
	case 0x26:
		return 34;
	case 0x25:
		return 33;
	case 0x24:
		return 32;
	case 0x23:
		return 31;
	case 0x22:
		return 30;
	case 0x21:
		return 29;
	case 0x1F:
		return 28;
	case 0x1E:
		return 27;
	case 0x1D:
		return 26;
	case 0x1C:
		return 25;
	case 0x1B:
		return 24;
	case 0x1A:
		return 23;
	case 0x19:
		return 22;
	case 0x18:
		return 21;
	case 0x17:
		return 20;
	case 0x16:
		return 19;
	case 0x15:
		return 18;
	case 0x14:
		return 17;
	case 0x13:
		return 16;
	case 0x12:
		return 15;
	case 0x11:
		return 14;
	case 0x0F:
		return 13;
	case 0x0E:
		return 12;
	case 0x0D:
		return 11;
	case 0x0C:
		return 10;
	case 0x0B:
		return 9;
	case 0x0A:
		return 8;
	case 0x09:
		return 7;
	case 0x08:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x04:
		return 2;
	case 0x03:
		return 1;
	default:
		return 0;
	}
}

static int sanfran64ui(int ffsan64ui) {
	switch (ffsan64ui) {

	case 0xFF:
		return 232;
	case 0xFE:
		return 231;
	case 0xFD:
		return 230;
	case 0xFC:
		return 229;
	case 0xFB:
		return 228;
	case 0xFA:
		return 227;
	case 0xF9:
		return 226;
	case 0xF8:
		return 225;
	case 0xF7:
		return 224;
	case 0xF6:
		return 223;
	case 0xF5:
		return 222;
	case 0xF4:
		return 221;
	case 0xF3:
		return 220;
	case 0xF2:
		return 219;
	case 0xF1:
		return 218;
	case 0xEF:
		return 217;
	case 0xEE:
		return 216;
	case 0xED:
		return 215;
	case 0xEC:
		return 214;
	case 0xEB:
		return 213;
	case 0xEA:
		return 212;
	case 0xE9:
		return 211;
	case 0xE8:
		return 210;
	case 0xE7:
		return 209;
	case 0xE6:
		return 208;
	case 0xE5:
		return 207;
	case 0xE4:
		return 206;
	case 0xE3:
		return 205;
	case 0xE2:
		return 204;
	case 0xE1:
		return 203;
	case 0xDF:
		return 202;
	case 0xDE:
		return 201;
	case 0xDD:
		return 200;
	case 0xDC:
		return 199;
	case 0xDB:
		return 198;
	case 0xDA:
		return 197;
	case 0xD9:
		return 196;
	case 0xD8:
		return 195;
	case 0xD7:
		return 194;
	case 0xD6:
		return 193;
	case 0xD5:
		return 192;
	case 0xD4:
		return 191;
	case 0xD3:
		return 190;
	case 0xD2:
		return 189;
	case 0xD1:
		return 188;
	case 0xCF:
		return 187;
	case 0xCE:
		return 186;
	case 0xCD:
		return 185;
	case 0xCC:
		return 184;
	case 0xCB:
		return 183;
	case 0xCA:
		return 182;
	case 0xC9:
		return 181;
	case 0xC8:
		return 180;
	case 0xC7:
		return 179;
	case 0xC6:
		return 178;
	case 0xC5:
		return 177;
	case 0xC4:
		return 176;
	case 0xC3:
		return 175;
	case 0xC2:
		return 174;
	case 0xC1:
		return 173;
	case 0xBF:
		return 172;
	case 0xBE:
		return 171;
	case 0xBD:
		return 170;
	case 0xBC:
		return 169;
	case 0xBB:
		return 168;
	case 0xBA:
		return 167;
	case 0xB9:
		return 166;
	case 0xB8:
		return 165;
	case 0xB7:
		return 164;
	case 0xB6:
		return 163;
	case 0xB5:
		return 162;
	case 0xB4:
		return 161;
	case 0xB3:
		return 160;
	case 0xB2:
		return 159;
	case 0xB1:
		return 158;
	case 0xAF:
		return 157;
	case 0xAE:
		return 156;
	case 0xAD:
		return 155;
	case 0xAC:
		return 154;
	case 0xAB:
		return 153;
	case 0xAA:
		return 152;
	case 0xA9:
		return 151;
	case 0xA8:
		return 150;
	case 0xA7:
		return 149;
	case 0xA6:
		return 148;
	case 0xA5:
		return 147;
	case 0xA4:
		return 146;
	case 0xA3:
		return 145;
	case 0xA2:
		return 144;
	case 0xA1:
		return 143;
	case 0x9F:
		return 142;
	case 0x9E:
		return 141;
	case 0x9D:
		return 140;
	case 0x9C:
		return 139;
	case 0x9B:
		return 138;
	case 0x9A:
		return 137;
	case 0x99:
		return 136;
	case 0x98:
		return 135;
	case 0x97:
		return 134;
	case 0x96:
		return 133;
	case 0x95:
		return 132;
	case 0x94:
		return 131;
	case 0x93:
		return 130;
	case 0x92:
		return 129;
	case 0x91:
		return 128;
	case 0x8F:
		return 127;
	case 0x8E:
		return 126;
	case 0x8D:
		return 125;
	case 0x8C:
		return 124;
	case 0x8B:
		return 123;
	case 0x8A:
		return 122;
	case 0x89:
		return 121;
	case 0x88:
		return 120;
	case 0x87:
		return 119;
	case 0x86:
		return 118;
	case 0x85:
		return 117;
	case 0x84:
		return 116;
	case 0x83:
		return 115;
	case 0x82:
		return 114;
	case 0x81:
		return 113;

	case 0x7F:
		return 112;
	case 0x7E:
		return 111;
	case 0x7D:
		return 110;
	case 0x7C:
		return 109;
	case 0x7B:
		return 108;
	case 0x7A:
		return 107;
	case 0x79:
		return 106;
	case 0x78:
		return 105;
	case 0x77:
		return 104;
	case 0x76:
		return 103;
	case 0x75:
		return 102;
	case 0x74:
		return 101;
	case 0x73:
		return 100;
	case 0x72:
		return 99;
	case 0x71:
		return 98;
	case 0x6F:
		return 97;
	case 0x6E:
		return 96;
	case 0x6D:
		return 95;
	case 0x6C:
		return 94;
	case 0x6B:
		return 93;
	case 0x6A:
		return 92;
	case 0x69:
		return 91;
	case 0x68:
		return 90;
	case 0x67:
		return 89;
	case 0x66:
		return 88;
	case 0x65:
		return 87;
	case 0x64:
		return 86;
	case 0x63:
		return 85;
	case 0x62:
		return 84;
	case 0x61:
		return 83;
	case 0x5F:
		return 82;
	case 0x5E:
		return 81;
	case 0x5D:
		return 80;
	case 0x5C:
		return 79;
	case 0x5B:
		return 78;
	case 0x5A:
		return 77;
	case 0x59:
		return 76;
	case 0x58:
		return 75;
	case 0x57:
		return 74;
	case 0x56:
		return 73;
	case 0x55:
		return 72;
	case 0x54:
		return 71;
	case 0x53:
		return 70;
	case 0x52:
		return 69;
	case 0x51:
		return 68;
	case 0x4F:
		return 67;
	case 0x4E:
		return 66;
	case 0x4D:
		return 65;
	case 0x4C:
		return 64;
	case 0x4B:
		return 63;
	case 0x4A:
		return 62;
	case 0x49:
		return 61;
	case 0x48:
		return 60;
	case 0x47:
		return 59;
	case 0x46:
		return 58;
	case 0x45:
		return 57;
	case 0x44:
		return 56;
	case 0x43:
		return 55;
	case 0x42:
		return 54;
	case 0x41:
		return 53;
	case 0x3F:
		return 52;
	case 0x3E:
		return 51;
	case 0x3D:
		return 50;
	case 0x3C:
		return 49;
	case 0x3B:
		return 48;
	case 0x3A:
		return 47;
	case 0x39:
		return 46;
	case 0x38:
		return 45;
	case 0x37:
		return 44;
	case 0x36:
		return 43;
	case 0x35:
		return 42;
	case 0x34:
		return 41;
	case 0x33:
		return 40;
	case 0x32:
		return 39;
	case 0x31:
		return 38;
	case 0x29:
		return 37;
	case 0x28:
		return 36;
	case 0x27:
		return 35;
	case 0x26:
		return 34;
	case 0x25:
		return 33;
	case 0x24:
		return 32;
	case 0x23:
		return 31;
	case 0x22:
		return 30;
	case 0x21:
		return 29;
	case 0x1F:
		return 28;
	case 0x1E:
		return 27;
	case 0x1D:
		return 26;
	case 0x1C:
		return 25;
	case 0x1B:
		return 24;
	case 0x1A:
		return 23;
	case 0x19:
		return 22;
	case 0x18:
		return 21;
	case 0x17:
		return 20;
	case 0x16:
		return 19;
	case 0x15:
		return 18;
	case 0x14:
		return 17;
	case 0x13:
		return 16;
	case 0x12:
		return 15;
	case 0x11:
		return 14;
	case 0x0F:
		return 13;
	case 0x0E:
		return 12;
	case 0x0D:
		return 11;
	case 0x0C:
		return 10;
	case 0x0B:
		return 9;
	case 0x0A:
		return 8;
	case 0x09:
		return 7;
	case 0x08:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x04:
		return 2;
	case 0x03:
		return 1;
	default:
		return 0;
	}
}

static int crusnwld64(int ffcru64) {
	switch (ffcru64) {

	case 0xFF:
		return 225;
	case 0xFE:
		return 224;
	case 0xFD:
		return 223;
	case 0xFC:
		return 222;
	case 0xFB:
		return 221;
	case 0xFA:
		return 220;
	case 0xF9:
		return 219;
	case 0xF8:
		return 218;
	case 0xF7:
		return 217;
	case 0xF6:
		return 216;
	case 0xF5:
		return 215;
	case 0xF4:
		return 214;
	case 0xF3:
		return 213;
	case 0xF2:
		return 212;
	case 0xF1:
		return 211;
	case 0xEF:
		return 210;
	case 0xEE:
		return 209;
	case 0xED:
		return 208;
	case 0xEC:
		return 207;
	case 0xEB:
		return 206;
	case 0xEA:
		return 205;
	case 0xE9:
		return 204;
	case 0xE8:
		return 203;
	case 0xE7:
		return 202;
	case 0xE6:
		return 201;
	case 0xE5:
		return 200;
	case 0xE4:
		return 199;
	case 0xE3:
		return 198;
	case 0xE2:
		return 197;
	case 0xE1:
		return 196;
	case 0xDF:
		return 195;
	case 0xDE:
		return 194;
	case 0xDD:
		return 193;
	case 0xDC:
		return 192;
	case 0xDB:
		return 191;
	case 0xDA:
		return 190;
	case 0xD9:
		return 189;
	case 0xD8:
		return 188;
	case 0xD7:
		return 187;
	case 0xD6:
		return 186;
	case 0xD5:
		return 185;
	case 0xD4:
		return 184;
	case 0xD3:
		return 183;
	case 0xD2:
		return 182;
	case 0xD1:
		return 181;
	case 0xCF:
		return 180;
	case 0xCE:
		return 179;
	case 0xCD:
		return 178;
	case 0xCC:
		return 177;
	case 0xCB:
		return 176;
	case 0xCA:
		return 175;
	case 0xC9:
		return 174;
	case 0xC7:
		return 173;
	case 0xC6:
		return 172;
	case 0xC5:
		return 171;
	case 0xC3:
		return 170;
	case 0xBF:
		return 169;
	case 0xBE:
		return 168;
	case 0xBD:
		return 167;
	case 0xBC:
		return 166;
	case 0xBB:
		return 165;
	case 0xBA:
		return 164;
	case 0xB9:
		return 163;
	case 0xB8:
		return 162;
	case 0xB7:
		return 161;
	case 0xB6:
		return 160;
	case 0xB5:
		return 159;
	case 0xB4:
		return 158;
	case 0xB3:
		return 157;
	case 0xB2:
		return 156;
	case 0xB1:
		return 155;
	case 0xAF:
		return 154;
	case 0xAE:
		return 153;
	case 0xAD:
		return 152;
	case 0xAC:
		return 151;
	case 0xAB:
		return 150;
	case 0xAA:
		return 149;
	case 0xA9:
		return 148;
	case 0xA8:
		return 147;
	case 0xA7:
		return 146;
	case 0xA6:
		return 145;
	case 0xA5:
		return 144;
	case 0xA4:
		return 143;
	case 0xA3:
		return 142;
	case 0xA2:
		return 141;
	case 0xA1:
		return 140;
	case 0x9F:
		return 139;
	case 0x9E:
		return 138;
	case 0x9D:
		return 137;
	case 0x9C:
		return 136;
	case 0x9B:
		return 135;
	case 0x9A:
		return 134;
	case 0x99:
		return 133;
	case 0x98:
		return 132;
	case 0x97:
		return 131;
	case 0x96:
		return 130;
	case 0x95:
		return 129;
	case 0x94:
		return 128;
	case 0x93:
		return 127;
	case 0x92:
		return 126;
	case 0x91:
		return 125;
	case 0x8F:
		return 124;
	case 0x8E:
		return 123;
	case 0x8D:
		return 122;
	case 0x8C:
		return 121;
	case 0x8B:
		return 120;
	case 0x8A:
		return 119;
	case 0x89:
		return 118;
	case 0x88:
		return 117;
	case 0x87:
		return 116;
	case 0x86:
		return 115;
	case 0x85:
		return 114;
	case 0x84:
		return 113;
	case 0x83:
		return 112;
	case 0x82:
		return 111;


	case 0x7E:
		return 110;
	case 0x7D:
		return 109;
	case 0x7C:
		return 108;
	case 0x7B:
		return 107;
	case 0x7A:
		return 106;
	case 0x79:
		return 105;
	case 0x78:
		return 104;
	case 0x77:
		return 103;
	case 0x76:
		return 102;
	case 0x75:
		return 101;
	case 0x74:
		return 100;
	case 0x73:
		return 99;
	case 0x72:
		return 98;
	case 0x71:
		return 97;
	case 0x6F:
		return 96;
	case 0x6E:
		return 95;
	case 0x6D:
		return 94;
	case 0x6C:
		return 93;
	case 0x6B:
		return 92;
	case 0x6A:
		return 91;
	case 0x69:
		return 90;
	case 0x68:
		return 89;
	case 0x67:
		return 88;
	case 0x66:
		return 87;
	case 0x65:
		return 86;
	case 0x64:
		return 85;
	case 0x63:
		return 84;
	case 0x62:
		return 83;
	case 0x61:
		return 82;
	case 0x5F:
		return 81;
	case 0x5E:
		return 80;
	case 0x5D:
		return 79;
	case 0x5C:
		return 78;
	case 0x5B:
		return 77;
	case 0x5A:
		return 76;
	case 0x59:
		return 75;
	case 0x58:
		return 74;
	case 0x57:
		return 73;
	case 0x56:
		return 72;
	case 0x55:
		return 71;
	case 0x54:
		return 70;
	case 0x53:
		return 69;
	case 0x52:
		return 68;
	case 0x51:
		return 67;
	case 0x4F:
		return 66;
	case 0x4E:
		return 65;
	case 0x4D:
		return 64;
	case 0x4C:
		return 63;
	case 0x4B:
		return 62;
	case 0x4A:
		return 61;
	case 0x49:
		return 60;
	case 0x48:
		return 59;
	case 0x47:
		return 58;
	case 0x46:
		return 57;
	case 0x45:
		return 56;
	case 0x44:
		return 55;
	case 0x43:
		return 54;
	case 0x42:
		return 53;
	case 0x41:
		return 52;
	case 0x3F:
		return 51;
	case 0x3E:
		return 50;
	case 0x3D:
		return 49;
	case 0x3C:
		return 48;
	case 0x3B:
		return 47;
	case 0x3A:
		return 46;
	case 0x39:
		return 45;
	case 0x38:
		return 44;
	case 0x37:
		return 43;
	case 0x36:
		return 42;
	case 0x35:
		return 41;
	case 0x34:
		return 40;
	case 0x33:
		return 39;
	case 0x32:
		return 38;
	case 0x31:
		return 37;
	case 0x29:
		return 36;
	case 0x28:
		return 35;
	case 0x27:
		return 34;
	case 0x26:
		return 33;
	case 0x25:
		return 32;
	case 0x24:
		return 31;
	case 0x23:
		return 30;
	case 0x22:
		return 29;
	case 0x21:
		return 28;
	case 0x1F:
		return 27;
	case 0x1E:
		return 26;
	case 0x1D:
		return 25;
	case 0x1C:
		return 24;
	case 0x1B:
		return 23;
	case 0x1A:
		return 22;
	case 0x19:
		return 21;
	case 0x18:
		return 20;
	case 0x17:
		return 19;
	case 0x16:
		return 18;
	case 0x15:
		return 17;
	case 0x14:
		return 16;
	case 0x13:
		return 15;
	case 0x12:
		return 14;
	case 0x11:
		return 13;
	case 0x0F:
		return 12;
	case 0x0E:
		return 11;
	case 0x0D:
		return 10;
	case 0x0B:
		return 8;
	case 0x0A:
		return 7;
	case 0x09:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

static int crusnwldui(int ffcruui) {
	switch (ffcruui) {

	case 0xFF:
		return 225;
	case 0xFE:
		return 224;
	case 0xFD:
		return 223;
	case 0xFC:
		return 222;
	case 0xFB:
		return 221;
	case 0xFA:
		return 220;
	case 0xF9:
		return 219;
	case 0xF8:
		return 218;
	case 0xF7:
		return 217;
	case 0xF6:
		return 216;
	case 0xF5:
		return 215;
	case 0xF4:
		return 214;
	case 0xF3:
		return 213;
	case 0xF2:
		return 212;
	case 0xF1:
		return 211;
	case 0xEF:
		return 210;
	case 0xEE:
		return 209;
	case 0xED:
		return 208;
	case 0xEC:
		return 207;
	case 0xEB:
		return 206;
	case 0xEA:
		return 205;
	case 0xE9:
		return 204;
	case 0xE8:
		return 203;
	case 0xE7:
		return 202;
	case 0xE6:
		return 201;
	case 0xE5:
		return 200;
	case 0xE4:
		return 199;
	case 0xE3:
		return 198;
	case 0xE2:
		return 197;
	case 0xE1:
		return 196;
	case 0xDF:
		return 195;
	case 0xDE:
		return 194;
	case 0xDD:
		return 193;
	case 0xDC:
		return 192;
	case 0xDB:
		return 191;
	case 0xDA:
		return 190;
	case 0xD9:
		return 189;
	case 0xD8:
		return 188;
	case 0xD7:
		return 187;
	case 0xD6:
		return 186;
	case 0xD5:
		return 185;
	case 0xD4:
		return 184;
	case 0xD3:
		return 183;
	case 0xD2:
		return 182;
	case 0xD1:
		return 181;
	case 0xCF:
		return 180;
	case 0xCE:
		return 179;
	case 0xCD:
		return 178;
	case 0xCC:
		return 177;
	case 0xCB:
		return 176;
	case 0xCA:
		return 175;
	case 0xC9:
		return 174;
	case 0xC7:
		return 173;
	case 0xC6:
		return 172;
	case 0xC5:
		return 171;
	case 0xC3:
		return 170;
	case 0xBF:
		return 169;
	case 0xBE:
		return 168;
	case 0xBD:
		return 167;
	case 0xBC:
		return 166;
	case 0xBB:
		return 165;
	case 0xBA:
		return 164;
	case 0xB9:
		return 163;
	case 0xB8:
		return 162;
	case 0xB7:
		return 161;
	case 0xB6:
		return 160;
	case 0xB5:
		return 159;
	case 0xB4:
		return 158;
	case 0xB3:
		return 157;
	case 0xB2:
		return 156;
	case 0xB1:
		return 155;
	case 0xAF:
		return 154;
	case 0xAE:
		return 153;
	case 0xAD:
		return 152;
	case 0xAC:
		return 151;
	case 0xAB:
		return 150;
	case 0xAA:
		return 149;
	case 0xA9:
		return 148;
	case 0xA8:
		return 147;
	case 0xA7:
		return 146;
	case 0xA6:
		return 145;
	case 0xA5:
		return 144;
	case 0xA4:
		return 143;
	case 0xA3:
		return 142;
	case 0xA2:
		return 141;
	case 0xA1:
		return 140;
	case 0x9F:
		return 139;
	case 0x9E:
		return 138;
	case 0x9D:
		return 137;
	case 0x9C:
		return 136;
	case 0x9B:
		return 135;
	case 0x9A:
		return 134;
	case 0x99:
		return 133;
	case 0x98:
		return 132;
	case 0x97:
		return 131;
	case 0x96:
		return 130;
	case 0x95:
		return 129;
	case 0x94:
		return 128;
	case 0x93:
		return 127;
	case 0x92:
		return 126;
	case 0x91:
		return 125;
	case 0x8F:
		return 124;
	case 0x8E:
		return 123;
	case 0x8D:
		return 122;
	case 0x8C:
		return 121;
	case 0x8B:
		return 120;
	case 0x8A:
		return 119;
	case 0x89:
		return 118;
	case 0x88:
		return 117;
	case 0x87:
		return 116;
	case 0x86:
		return 115;
	case 0x85:
		return 114;
	case 0x84:
		return 113;
	case 0x83:
		return 112;
	case 0x82:
		return 111;


	case 0x7E:
		return 110;
	case 0x7D:
		return 109;
	case 0x7C:
		return 108;
	case 0x7B:
		return 107;
	case 0x7A:
		return 106;
	case 0x79:
		return 105;
	case 0x78:
		return 104;
	case 0x77:
		return 103;
	case 0x76:
		return 102;
	case 0x75:
		return 101;
	case 0x74:
		return 100;
	case 0x73:
		return 99;
	case 0x72:
		return 98;
	case 0x71:
		return 97;
	case 0x6F:
		return 96;
	case 0x6E:
		return 95;
	case 0x6D:
		return 94;
	case 0x6C:
		return 93;
	case 0x6B:
		return 92;
	case 0x6A:
		return 91;
	case 0x69:
		return 90;
	case 0x68:
		return 89;
	case 0x67:
		return 88;
	case 0x66:
		return 87;
	case 0x65:
		return 86;
	case 0x64:
		return 85;
	case 0x63:
		return 84;
	case 0x62:
		return 83;
	case 0x61:
		return 82;
	case 0x5F:
		return 81;
	case 0x5E:
		return 80;
	case 0x5D:
		return 79;
	case 0x5C:
		return 78;
	case 0x5B:
		return 77;
	case 0x5A:
		return 76;
	case 0x59:
		return 75;
	case 0x58:
		return 74;
	case 0x57:
		return 73;
	case 0x56:
		return 72;
	case 0x55:
		return 71;
	case 0x54:
		return 70;
	case 0x53:
		return 69;
	case 0x52:
		return 68;
	case 0x51:
		return 67;
	case 0x4F:
		return 66;
	case 0x4E:
		return 65;
	case 0x4D:
		return 64;
	case 0x4C:
		return 63;
	case 0x4B:
		return 62;
	case 0x4A:
		return 61;
	case 0x49:
		return 60;
	case 0x48:
		return 59;
	case 0x47:
		return 58;
	case 0x46:
		return 57;
	case 0x45:
		return 56;
	case 0x44:
		return 55;
	case 0x43:
		return 54;
	case 0x42:
		return 53;
	case 0x41:
		return 52;
	case 0x3F:
		return 51;
	case 0x3E:
		return 50;
	case 0x3D:
		return 49;
	case 0x3C:
		return 48;
	case 0x3B:
		return 47;
	case 0x3A:
		return 46;
	case 0x39:
		return 45;
	case 0x38:
		return 44;
	case 0x37:
		return 43;
	case 0x36:
		return 42;
	case 0x35:
		return 41;
	case 0x34:
		return 40;
	case 0x33:
		return 39;
	case 0x32:
		return 38;
	case 0x31:
		return 37;
	case 0x29:
		return 36;
	case 0x28:
		return 35;
	case 0x27:
		return 34;
	case 0x26:
		return 33;
	case 0x25:
		return 32;
	case 0x24:
		return 31;
	case 0x23:
		return 30;
	case 0x22:
		return 29;
	case 0x21:
		return 28;
	case 0x1F:
		return 27;
	case 0x1E:
		return 26;
	case 0x1D:
		return 25;
	case 0x1C:
		return 24;
	case 0x1B:
		return 23;
	case 0x1A:
		return 22;
	case 0x19:
		return 21;
	case 0x18:
		return 20;
	case 0x17:
		return 19;
	case 0x16:
		return 18;
	case 0x15:
		return 17;
	case 0x14:
		return 16;
	case 0x13:
		return 15;
	case 0x12:
		return 14;
	case 0x11:
		return 13;
	case 0x0F:
		return 12;
	case 0x0E:
		return 11;
	case 0x0D:
		return 10;
	case 0x0C:
		return 9;
	case 0x0B:
		return 8;
	case 0x0A:
		return 7;
	case 0x09:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

static int crusnusa64(int ffusa) {
	switch (ffusa) {

	case 0xFF:
		return 214;
	case 0xFE:
		return 213;
	case 0xFC:
		return 212;
	case 0xFB:
		return 211;
	case 0xFA:
		return 210;
	case 0xF9:
		return 209;
	case 0xF8:
		return 208;
	case 0xF7:
		return 207;
	case 0xF6:
		return 206;
	case 0xF5:
		return 205;
	case 0xF4:
		return 204;
	case 0xF3:
		return 203;
	case 0xF2:
		return 202;
	case 0xF1:
		return 201;
	case 0xEF:
		return 200;
	case 0xEE:
		return 199;
	case 0xED:
		return 198;
	case 0xEC:
		return 197;
	case 0xEB:
		return 196;
	case 0xEA:
		return 195;
	case 0xE9:
		return 194;
	case 0xE8:
		return 193;
	case 0xE7:
		return 192;
	case 0xE6:
		return 191;
	case 0xE5:
		return 190;
	case 0xE4:
		return 189;
	case 0xE3:
		return 188;
	case 0xE2:
		return 187;
	case 0xE1:
		return 186;
	case 0xDF:
		return 185;
	case 0xDE:
		return 184;
	case 0xDD:
		return 183;
	case 0xDC:
		return 182;
	case 0xDB:
		return 181;
	case 0xDA:
		return 180;
	case 0xD9:
		return 179;
	case 0xD8:
		return 178;
	case 0xD7:
		return 177;
	case 0xD3:
		return 176;
	case 0xD2:
		return 175;
	case 0xD1:
		return 174;
	case 0xCF:
		return 173;
	case 0xCE:
		return 172;
	case 0xCD:
		return 171;
	case 0xCC:
		return 170;
	case 0xCB:
		return 169;
	case 0xCA:
		return 168;
	case 0xC9:
		return 167;
	case 0xC7:
		return 166;
	case 0xC6:
		return 165;
	case 0xC5:
		return 164;
	case 0xC3:
		return 163;
	case 0xBF:
		return 162;
	case 0xBE:
		return 161;
	case 0xBD:
		return 160;
	case 0xBC:
		return 159;
	case 0xBB:
		return 158;
	case 0xBA:
		return 157;
	case 0xB9:
		return 156;
	case 0xB8:
		return 155;
	case 0xB7:
		return 154;
	case 0xB6:
		return 153;
	case 0xB5:
		return 152;
	case 0xB4:
		return 151;
	case 0xB3:
		return 150;
	case 0xB2:
		return 149;
	case 0xB1:
		return 148;
	case 0xAF:
		return 147;
	case 0xAE:
		return 146;
	case 0xAD:
		return 145;
	case 0xAC:
		return 144;
	case 0xAB:
		return 143;
	case 0xAA:
		return 142;
	case 0xA9:
		return 141;
	case 0xA8:
		return 140;
	case 0xA7:
		return 139;
	case 0xA6:
		return 138;
	case 0xA5:
		return 137;
	case 0xA4:
		return 136;
	case 0xA3:
		return 135;
	case 0xA2:
		return 134;
	case 0xA1:
		return 133;
	case 0x9F:
		return 132;
	case 0x9E:
		return 131;
	case 0x9D:
		return 130;
	case 0x9C:
		return 129;
	case 0x9B:
		return 128;
	case 0x9A:
		return 127;
	case 0x99:
		return 126;
	case 0x98:
		return 125;
	case 0x97:
		return 124;
	case 0x96:
		return 123;
	case 0x95:
		return 122;
	case 0x94:
		return 121;
	case 0x93:
		return 120;
	case 0x92:
		return 119;
	case 0x91:
		return 118;
	case 0x8F:
		return 117;
	case 0x8E:
		return 116;
	case 0x8D:
		return 115;
	case 0x8C:
		return 114;
	case 0x8B:
		return 113;
	case 0x8A:
		return 112;
	case 0x89:
		return 111;
	case 0x88:
		return 110;
	case 0x87:
		return 109;
	case 0x86:
		return 108;
	case 0x84:
		return 107;
	case 0x83:
		return 106;
	case 0x82:
		return 105;


	case 0x7E:
		return 104;
	case 0x7D:
		return 103;
	case 0x7C:
		return 102;
	case 0x7B:
		return 101;
	case 0x7A:
		return 100;
	case 0x79:
		return 99;
	case 0x78:
		return 98;
	case 0x77:
		return 97;
	case 0x76:
		return 96;
	case 0x75:
		return 95;
	case 0x74:
		return 94;
	case 0x73:
		return 93;
	case 0x71:
		return 92;
	case 0x6F:
		return 91;
	case 0x6E:
		return 90;
	case 0x6D:
		return 89;
	case 0x6C:
		return 88;
	case 0x6B:
		return 87;
	case 0x6A:
		return 86;
	case 0x69:
		return 85;
	case 0x68:
		return 84;
	case 0x67:
		return 83;
	case 0x66:
		return 82;
	case 0x65:
		return 81;
	case 0x64:
		return 80;
	case 0x63:
		return 79;
	case 0x62:
		return 78;
	case 0x61:
		return 77;
	case 0x5F:
		return 76;
	case 0x5E:
		return 75;
	case 0x5D:
		return 74;
	case 0x5C:
		return 73;
	case 0x5B:
		return 72;
	case 0x5A:
		return 71;
	case 0x59:
		return 70;
	case 0x58:
		return 69;
	case 0x57:
		return 68;
	case 0x56:
		return 67;
	case 0x55:
		return 66;
	case 0x54:
		return 65;
	case 0x53:
		return 64;
	case 0x52:
		return 63;
	case 0x51:
		return 62;
	case 0x4F:
		return 61;
	case 0x4E:
		return 60;
	case 0x4D:
		return 59;
	case 0x4C:
		return 58;
	case 0x4B:
		return 57;
	case 0x4A:
		return 56;
	case 0x49:
		return 55;
	case 0x48:
		return 54;
	case 0x47:
		return 53;
	case 0x46:
		return 52;
	case 0x45:
		return 51;
	case 0x44:
		return 50;
	case 0x43:
		return 49;
	case 0x42:
		return 48;
	case 0x41:
		return 47;
	case 0x3F:
		return 46;
	case 0x3E:
		return 45;
	case 0x3D:
		return 44;
	case 0x3B:
		return 43;
	case 0x3A:
		return 42;
	case 0x39:
		return 41;
	case 0x38:
		return 40;
	case 0x37:
		return 39;
	case 0x36:
		return 38;
	case 0x35:
		return 37;
	case 0x34:
		return 36;
	case 0x33:
		return 35;
	case 0x32:
		return 34;
	case 0x31:
		return 33;
	case 0x29:
		return 32;
	case 0x28:
		return 31;
	case 0x27:
		return 30;
	case 0x26:
		return 29;
	case 0x25:
		return 28;
	case 0x24:
		return 27;
	case 0x23:
		return 26;
	case 0x22:
		return 25;
	case 0x21:
		return 24;
	case 0x1F:
		return 23;
	case 0x1E:
		return 22;
	case 0x1D:
		return 21;
	case 0x1B:
		return 20;
	case 0x1A:
		return 19;
	case 0x19:
		return 18;
	case 0x18:
		return 17;
	case 0x17:
		return 16;
	case 0x16:
		return 15;
	case 0x15:
		return 14;
	case 0x14:
		return 13;
	case 0x13:
		return 12;
	case 0x12:
		return 11;
	case 0x11:
		return 10;
	case 0x0F:
		return 9;
	case 0x0D:
		return 8;
	case 0x0C:
		return 7;
	case 0x0B:
		return 6;
	case 0x09:
		return 5;
	case 0x07:
		return 4;
	case 0x06:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

static int crusnusaui(int ffusa) {
	switch (ffusa) {

	case 0xFF:
		return 214;
	case 0xFE:
		return 213;
	case 0xFC:
		return 212;
	case 0xFB:
		return 211;
	case 0xFA:
		return 210;
	case 0xF9:
		return 209;
	case 0xF8:
		return 208;
	case 0xF7:
		return 207;
	case 0xF6:
		return 206;
	case 0xF5:
		return 205;
	case 0xF4:
		return 204;
	case 0xF3:
		return 203;
	case 0xF2:
		return 202;
	case 0xF1:
		return 201;
	case 0xEF:
		return 200;
	case 0xEE:
		return 199;
	case 0xED:
		return 198;
	case 0xEC:
		return 197;
	case 0xEB:
		return 196;
	case 0xEA:
		return 195;
	case 0xE9:
		return 194;
	case 0xE8:
		return 193;
	case 0xE7:
		return 192;
	case 0xE6:
		return 191;
	case 0xE5:
		return 190;
	case 0xE4:
		return 189;
	case 0xE3:
		return 188;
	case 0xE2:
		return 187;
	case 0xE1:
		return 186;
	case 0xDF:
		return 185;
	case 0xDE:
		return 184;
	case 0xDD:
		return 183;
	case 0xDC:
		return 182;
	case 0xDB:
		return 181;
	case 0xDA:
		return 180;
	case 0xD9:
		return 179;
	case 0xD8:
		return 178;
	case 0xD7:
		return 177;
	case 0xD3:
		return 176;
	case 0xD2:
		return 175;
	case 0xD1:
		return 174;
	case 0xCF:
		return 173;
	case 0xCE:
		return 172;
	case 0xCD:
		return 171;
	case 0xCC:
		return 170;
	case 0xCB:
		return 169;
	case 0xCA:
		return 168;
	case 0xC9:
		return 167;
	case 0xC7:
		return 166;
	case 0xC6:
		return 165;
	case 0xC5:
		return 164;
	case 0xC3:
		return 163;
	case 0xBF:
		return 162;
	case 0xBE:
		return 161;
	case 0xBD:
		return 160;
	case 0xBC:
		return 159;
	case 0xBB:
		return 158;
	case 0xBA:
		return 157;
	case 0xB9:
		return 156;
	case 0xB8:
		return 155;
	case 0xB7:
		return 154;
	case 0xB6:
		return 153;
	case 0xB5:
		return 152;
	case 0xB4:
		return 151;
	case 0xB3:
		return 150;
	case 0xB2:
		return 149;
	case 0xB1:
		return 148;
	case 0xAF:
		return 147;
	case 0xAE:
		return 146;
	case 0xAD:
		return 145;
	case 0xAC:
		return 144;
	case 0xAB:
		return 143;
	case 0xAA:
		return 142;
	case 0xA9:
		return 141;
	case 0xA8:
		return 140;
	case 0xA7:
		return 139;
	case 0xA6:
		return 138;
	case 0xA5:
		return 137;
	case 0xA4:
		return 136;
	case 0xA3:
		return 135;
	case 0xA2:
		return 134;
	case 0xA1:
		return 133;
	case 0x9F:
		return 132;
	case 0x9E:
		return 131;
	case 0x9D:
		return 130;
	case 0x9C:
		return 129;
	case 0x9B:
		return 128;
	case 0x9A:
		return 127;
	case 0x99:
		return 126;
	case 0x98:
		return 125;
	case 0x97:
		return 124;
	case 0x96:
		return 123;
	case 0x95:
		return 122;
	case 0x94:
		return 121;
	case 0x93:
		return 120;
	case 0x92:
		return 119;
	case 0x91:
		return 118;
	case 0x8F:
		return 117;
	case 0x8E:
		return 116;
	case 0x8D:
		return 115;
	case 0x8C:
		return 114;
	case 0x8B:
		return 113;
	case 0x8A:
		return 112;
	case 0x89:
		return 111;
	case 0x88:
		return 110;
	case 0x87:
		return 109;
	case 0x86:
		return 108;
	case 0x84:
		return 107;
	case 0x83:
		return 106;
	case 0x82:
		return 105;


	case 0x7E:
		return 104;
	case 0x7D:
		return 103;
	case 0x7C:
		return 102;
	case 0x7B:
		return 101;
	case 0x7A:
		return 100;
	case 0x79:
		return 99;
	case 0x78:
		return 98;
	case 0x77:
		return 97;
	case 0x76:
		return 96;
	case 0x75:
		return 95;
	case 0x74:
		return 94;
	case 0x73:
		return 93;
	case 0x71:
		return 92;
	case 0x6F:
		return 91;
	case 0x6E:
		return 90;
	case 0x6D:
		return 89;
	case 0x6C:
		return 88;
	case 0x6B:
		return 87;
	case 0x6A:
		return 86;
	case 0x69:
		return 85;
	case 0x68:
		return 84;
	case 0x67:
		return 83;
	case 0x66:
		return 82;
	case 0x65:
		return 81;
	case 0x64:
		return 80;
	case 0x63:
		return 79;
	case 0x62:
		return 78;
	case 0x61:
		return 77;
	case 0x5F:
		return 76;
	case 0x5E:
		return 75;
	case 0x5D:
		return 74;
	case 0x5C:
		return 73;
	case 0x5B:
		return 72;
	case 0x5A:
		return 71;
	case 0x59:
		return 70;
	case 0x58:
		return 69;
	case 0x57:
		return 68;
	case 0x56:
		return 67;
	case 0x55:
		return 66;
	case 0x54:
		return 65;
	case 0x53:
		return 64;
	case 0x52:
		return 63;
	case 0x51:
		return 62;
	case 0x4F:
		return 61;
	case 0x4E:
		return 60;
	case 0x4D:
		return 59;
	case 0x4C:
		return 58;
	case 0x4B:
		return 57;
	case 0x4A:
		return 56;
	case 0x49:
		return 55;
	case 0x48:
		return 54;
	case 0x47:
		return 53;
	case 0x46:
		return 52;
	case 0x45:
		return 51;
	case 0x44:
		return 50;
	case 0x43:
		return 49;
	case 0x42:
		return 48;
	case 0x41:
		return 47;
	case 0x3F:
		return 46;
	case 0x3E:
		return 45;
	case 0x3D:
		return 44;
	case 0x3B:
		return 43;
	case 0x3A:
		return 42;
	case 0x39:
		return 41;
	case 0x38:
		return 40;
	case 0x37:
		return 39;
	case 0x36:
		return 38;
	case 0x35:
		return 37;
	case 0x34:
		return 36;
	case 0x33:
		return 35;
	case 0x32:
		return 34;
	case 0x31:
		return 33;
	case 0x29:
		return 32;
	case 0x28:
		return 31;
	case 0x27:
		return 30;
	case 0x26:
		return 29;
	case 0x25:
		return 28;
	case 0x24:
		return 27;
	case 0x23:
		return 26;
	case 0x22:
		return 25;
	case 0x21:
		return 24;
	case 0x1F:
		return 23;
	case 0x1E:
		return 22;
	case 0x1D:
		return 21;
	case 0x1B:
		return 20;
	case 0x1A:
		return 19;
	case 0x19:
		return 18;
	case 0x18:
		return 17;
	case 0x17:
		return 16;
	case 0x16:
		return 15;
	case 0x15:
		return 14;
	case 0x14:
		return 13;
	case 0x13:
		return 12;
	case 0x12:
		return 11;
	case 0x11:
		return 10;
	case 0x0F:
		return 9;
	case 0x0D:
		return 8;
	case 0x0C:
		return 7;
	case 0x0B:
		return 6;
	case 0x09:
		return 5;
	case 0x07:
		return 4;
	case 0x06:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

static int raveracer64(int ffRaw64) {
	switch (ffRaw64) {

		//case 0xFE:
		//return 128;
	case 0x7E:
		return 123;
		//case 0xBE:
		//return 126;
	case 0x3E:
		return 122;
	case 0xDE:
		return 121;
	case 0x5E:
		return 120;
	case 0x9E:
		return 119;
	case 0x1E:
		return 118;
	case 0xEE:
		return 117;
	case 0x6E:
		return 116;
	case 0xAE:
		return 115;
	case 0xCE:
		return 114;
	case 0x2E:
		return 113;
	case 0x4E:
		return 112;
	case 0x8E:
		return 111;
	case 0x0E:
		return 110;
	case 0xF6:
		return 109;
	case 0x76:
		return 108;
	case 0xB6:
		return 107;
	case 0x36:
		return 106;
	case 0xD6:
		return 105;
	case 0x56:
		return 104;
	case 0x96:
		return 103;
	case 0x16:
		return 102;
	case 0xE6:
		return 101;
	case 0x66:
		return 100;
	case 0xA6:
		return 99;
	case 0xC6:
		return 98;
	case 0x26:
		return 97;
	case 0x46:
		return 96;
	case 0x86:
		return 95;
	case 0x06:
		return 94;
	case 0xFA:
		return 93;
	case 0x7A:
		return 92;
	case 0xBA:
		return 91;
	case 0x3A:
		return 90;
	case 0xDA:
		return 89;
	case 0x5A:
		return 88;
	case 0x9A:
		return 87;
	case 0x1A:
		return 86;
	case 0xEA:
		return 85;
	case 0x6A:
		return 84;
	case 0xAA:
		return 83;
	case 0xCA:
		return 82;
	case 0x2A:
		return 81;
	case 0x4A:
		return 80;
	case 0x8A:
		return 79;
	case 0x0A:
		return 78;
	case 0xF2:
		return 77;
	case 0x72:
		return 76;
	case 0xB2:
		return 75;
	case 0x32:
		return 74;
	case 0xD2:
		return 73;
	case 0x52:
		return 72;
	case 0x92:
		return 71;
	case 0x12:
		return 70;
	case 0xE2:
		return 69;
	case 0x62:
		return 68;
	case 0xA2:
		return 67;
	case 0xC2:
		return 66;
	case 0x22:
		return 65;
	case 0x42:
		return 64;
	case 0x82:
		return 63;
	case 0x02:
		return 62;


	case 0x80:
		return 61;
	case 0x40:
		return 60;
	case 0x20:
		return 59;
	case 0xC0:
		return 58;
	case 0xA0:
		return 57;
	case 0x60:
		return 56;
	case 0xE0:
		return 55;
	case 0x10:
		return 54;
	case 0x90:
		return 53;
	case 0x50:
		return 52;
	case 0xD0:
		return 51;
	case 0x30:
		return 50;
	case 0xB0:
		return 49;
	case 0x70:
		return 48;
	case 0xF0:
		return 47;
	case 0x08:
		return 46;
	case 0x88:
		return 45;
	case 0x48:
		return 44;
	case 0x28:
		return 43;
	case 0xC8:
		return 42;
	case 0xA8:
		return 41;
	case 0x68:
		return 40;
	case 0xE8:
		return 39;
	case 0x18:
		return 38;
	case 0x98:
		return 37;
	case 0x58:
		return 36;
	case 0xD8:
		return 35;
	case 0x38:
		return 34;
	case 0xB8:
		return 33;
	case 0x78:
		return 32;
	case 0xF8:
		return 31;
	case 0x04:
		return 30;
	case 0x84:
		return 29;
	case 0x44:
		return 28;
	case 0x24:
		return 27;
	case 0xC4:
		return 26;
	case 0xA4:
		return 25;
	case 0x64:
		return 24;
	case 0xE4:
		return 23;
	case 0x14:
		return 22;
	case 0x94:
		return 21;
	case 0x54:
		return 20;
	case 0xD4:
		return 19;
	case 0x34:
		return 18;
	case 0xB4:
		return 17;
	case 0x74:
		return 16;
	case 0xF4:
		return 15;
	case 0x0C:
		return 14;
	case 0x8C:
		return 13;
	case 0x4C:
		return 12;
	case 0x2C:
		return 11;
	case 0xCC:
		return 10;
	case 0xAC:
		return 9;
	case 0x6C:
		return 8;
	case 0xEC:
		return 7;
	case 0x1C:
		return 6;
	case 0x9C:
		return 5;
	case 0x5C:
		return 4;
	case 0xDC:
		return 3;
	case 0x3C:
		return 2;
		//case 0xBC:
		//return 3;
	case 0x7C:
		return 1;
		//case 0xFC:
		//return 1;
	}
}

static int raveracerui64(int ffRawui64) {
	switch (ffRawui64) {

		//case 0xFE:
		//return 128;
	case 0x7E:
		return 123;
		//case 0xBE:
		//return 126;
	case 0x3E:
		return 122;
	case 0xDE:
		return 121;
	case 0x5E:
		return 120;
	case 0x9E:
		return 119;
	case 0x1E:
		return 118;
	case 0xEE:
		return 117;
	case 0x6E:
		return 116;
	case 0xAE:
		return 115;
	case 0xCE:
		return 114;
	case 0x2E:
		return 113;
	case 0x4E:
		return 112;
	case 0x8E:
		return 111;
	case 0x0E:
		return 110;
	case 0xF6:
		return 109;
	case 0x76:
		return 108;
	case 0xB6:
		return 107;
	case 0x36:
		return 106;
	case 0xD6:
		return 105;
	case 0x56:
		return 104;
	case 0x96:
		return 103;
	case 0x16:
		return 102;
	case 0xE6:
		return 101;
	case 0x66:
		return 100;
	case 0xA6:
		return 99;
	case 0xC6:
		return 98;
	case 0x26:
		return 97;
	case 0x46:
		return 96;
	case 0x86:
		return 95;
	case 0x06:
		return 94;
	case 0xFA:
		return 93;
	case 0x7A:
		return 92;
	case 0xBA:
		return 91;
	case 0x3A:
		return 90;
	case 0xDA:
		return 89;
	case 0x5A:
		return 88;
	case 0x9A:
		return 87;
	case 0x1A:
		return 86;
	case 0xEA:
		return 85;
	case 0x6A:
		return 84;
	case 0xAA:
		return 83;
	case 0xCA:
		return 82;
	case 0x2A:
		return 81;
	case 0x4A:
		return 80;
	case 0x8A:
		return 79;
	case 0x0A:
		return 78;
	case 0xF2:
		return 77;
	case 0x72:
		return 76;
	case 0xB2:
		return 75;
	case 0x32:
		return 74;
	case 0xD2:
		return 73;
	case 0x52:
		return 72;
	case 0x92:
		return 71;
	case 0x12:
		return 70;
	case 0xE2:
		return 69;
	case 0x62:
		return 68;
	case 0xA2:
		return 67;
	case 0xC2:
		return 66;
	case 0x22:
		return 65;
	case 0x42:
		return 64;
	case 0x82:
		return 63;
	case 0x02:
		return 62;


	case 0x80:
		return 61;
	case 0x40:
		return 60;
	case 0x20:
		return 59;
	case 0xC0:
		return 58;
	case 0xA0:
		return 57;
	case 0x60:
		return 56;
	case 0xE0:
		return 55;
	case 0x10:
		return 54;
	case 0x90:
		return 53;
	case 0x50:
		return 52;
	case 0xD0:
		return 51;
	case 0x30:
		return 50;
	case 0xB0:
		return 49;
	case 0x70:
		return 48;
	case 0xF0:
		return 47;
	case 0x08:
		return 46;
	case 0x88:
		return 45;
	case 0x48:
		return 44;
	case 0x28:
		return 43;
	case 0xC8:
		return 42;
	case 0xA8:
		return 41;
	case 0x68:
		return 40;
	case 0xE8:
		return 39;
	case 0x18:
		return 38;
	case 0x98:
		return 37;
	case 0x58:
		return 36;
	case 0xD8:
		return 35;
	case 0x38:
		return 34;
	case 0xB8:
		return 33;
	case 0x78:
		return 32;
	case 0xF8:
		return 31;
	case 0x04:
		return 30;
	case 0x84:
		return 29;
	case 0x44:
		return 28;
	case 0x24:
		return 27;
	case 0xC4:
		return 26;
	case 0xA4:
		return 25;
	case 0x64:
		return 24;
	case 0xE4:
		return 23;
	case 0x14:
		return 22;
	case 0x94:
		return 21;
	case 0x54:
		return 20;
	case 0xD4:
		return 19;
	case 0x34:
		return 18;
	case 0xB4:
		return 17;
	case 0x74:
		return 16;
	case 0xF4:
		return 15;
	case 0x0C:
		return 14;
	case 0x8C:
		return 13;
	case 0x4C:
		return 12;
	case 0x2C:
		return 11;
	case 0xCC:
		return 10;
	case 0xAC:
		return 9;
	case 0x6C:
		return 8;
	case 0xEC:
		return 7;
	case 0x1C:
		return 6;
	case 0x9C:
		return 5;
	case 0x5C:
		return 4;
	case 0xDC:
		return 3;
	case 0x3C:
		return 2;
		//case 0xBC:
		//return 3;
	case 0x7C:
		return 1;
		//case 0xFC:
		//return 1;
	}
}

void Mame020664bit::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	HWND hWnds = FindWindow(NULL, _T("MAME: San Francisco Rush 2049 [sf2049]"));
	HWND hWnd = FindWindowA(0, ("MAME: San Francisco Rush: The Rock (boot rom L 1.0, GUTS Oct 6 1997 / MAIN Oct 16 1997) [sfrushrk]"));
	HWND hWnd1 = FindWindowA(0, ("MAME: San Francisco Rush (boot rom L 1.0) [sfrush]"));
	HWND hWnd2 = FindWindowA(0, ("MAME: San Francisco Rush: The Rock (Wavenet, boot rom L 1.38, GUTS Aug 6 1997 / MAIN Aug 5 1997) [sfrushrkwo]"));
	HWND hWnd3 = FindWindowA(0, ("MAME: San Francisco Rush 2049: Special Edition [sf2049se]"));
	HWND hWnd4 = FindWindowA(0, ("MAME: Rave Racer (Rev. RV2, World) [raveracw]"));
	HWND hWnd5 = FindWindowA(0, ("MAME: Rave Racer (Rev. RV1 Ver.B, Japan) [raveracj]"));
	HWND hWnd6 = FindWindowA(0, ("MAME: Rave Racer (Rev. RV1, Japan) [raveracja]"));
	HWND hWnd7 = FindWindowA(0, ("MAME: San Francisco Rush (boot rom L 1.06A) [sfrusha]"));
	HWND hWnd8 = FindWindowA(0, ("MAME: San Francisco Rush 2049: Tournament Edition [sf2049te]"));
	HWND hWnd9 = FindWindowA(0, ("MAME: California Speed (Version 2.1a Apr 17 1998, GUTS 1.25 Apr 17 1998 / MAIN Apr 17 1998) [calspeed]"));
	HWND hWnd10 = FindWindowA(0, ("MAME: California Speed (Version 1.0r8 Mar 10 1998, GUTS Mar 10 1998 / MAIN Mar 10 1998) [calspeeda]"));
	HWND hWnd11 = FindWindowA(0, ("MAME: California Speed (Version 1.0r7a Mar 4 1998, GUTS Mar 3 1998 / MAIN Jan 19 1998) [calspeedb]"));
	HWND hWnd12 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.5) [crusnwld]"));
	HWND hWnd13 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.4) [crusnwld24]"));
	HWND hWnd14 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.3) [crusnwld23]"));
	HWND hWnd15 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.0) [crusnwld20]"));
	HWND hWnd16 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.9) [crusnwld19]"));
	HWND hWnd17 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.7) [crusnwld17]"));
	HWND hWnd18 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.3) [crusnwld13]"));
	HWND hWnd19 = FindWindowA(0, ("MAME: Cruis'n USA (rev L4.1) [crusnusa]"));
	HWND hWnd20 = FindWindowA(0, ("MAME: Cruis'n USA (rev L4.0) [crusnusa40]"));
	HWND hWnd21 = FindWindowA(0, ("MAME: Cruis'n USA (rev L2.1) [crusnusa21]"));
	HWND hWnd22 = FindWindowA(0, ("MAME: Off Road Challenge (v1.63) [offroadc]"));
	HWND hWnd23 = FindWindowA(0, ("MAME: Off Road Challenge (v1.63) [offroadc]"));
	HWND hWnd24 = FindWindowA(0, ("MAME: Off Road Challenge (v1.40) [offroadc4]"));
	HWND hWnd25 = FindWindowA(0, ("MAME: Off Road Challenge (v1.30) [offroadc3]"));
	HWND hWnd26 = FindWindowA(0, ("MAME: Off Road Challenge (v1.10) [offroadc1]"));

	if (hWnds > NULL)
	{
		INT_PTR ff204964 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ff2049164 = helpers->ReadIntPtr(ff204964 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264 = helpers->ReadIntPtr(ff2049164 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364 = helpers->ReadIntPtr(ff2049264 + 0x540, /* isRelativeOffset*/ false);
		UINT8 ff2049564 = helpers->ReadByte(ff2049364 + 0x7FC, /* isRelativeOffset */ false); //SanFranRush204964bit
		INT_PTR ff204964ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ff2049164ui = helpers->ReadIntPtr(ff204964ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264ui = helpers->ReadIntPtr(ff2049164ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364ui = helpers->ReadIntPtr(ff2049264ui + 0x7F0, /* isRelativeOffset*/ false);
		INT_PTR ff2049464ui = helpers->ReadIntPtr(ff2049364ui + 0x48, /* isRelativeOffset*/ false);
		UINT8 ff2049564ui = helpers->ReadByte(ff2049464ui + 0x62C, /* isRelativeOffset */ false); //SanFranRush204964bitmameUI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ff2049564);
		std::string ffs2 = std::to_string(ff2049564ui);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd > NULL)
	{
		int ffsanfranrush64 = 0;
		int ffsanfranrush64ui = 0;
		{
			INT_PTR ff64 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x540, /* isRelativeOffset*/ false);
			INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x68, /* isRelativeOffset*/ false);
			UINT8 ffsan64 = helpers->ReadByte(ff464 + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit
			INT_PTR ff64ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x5A0, /* isRelativeOffset*/ false);
			INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x8, /* isRelativeOffset*/ false);
			UINT8 ffsan64ui = helpers->ReadByte(ff464ui + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit mameui
			std::string ffs1 = std::to_string(ffsan64);
			std::string ffs2 = std::to_string(ffsan64ui);
			helpers->log((char *)ffs1.c_str());
			helpers->log("got value: ");
			ffsanfranrush64 = sanfran64(ffsan64);
			ffsanfranrush64ui = sanfran64ui(ffsan64ui);

			if (FFBMode == 0)
			{
				if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64ui) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64ui) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64ui) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64ui) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	else if (hWnd1 > NULL)
	{
	int ffsanfranrush64 = 0;
	int ffsanfranrush64ui = 0;
	{
		INT_PTR ff64 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x540, /* isRelativeOffset*/ false);
		INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x68, /* isRelativeOffset*/ false);
		UINT8 ffsan64 = helpers->ReadByte(ff464 + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit
		INT_PTR ff64ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x5A0, /* isRelativeOffset*/ false);
		INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x8, /* isRelativeOffset*/ false);
		UINT8 ffsan64ui = helpers->ReadByte(ff464ui + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit mameui
		std::string ffs1 = std::to_string(ffsan64);
		std::string ffs2 = std::to_string(ffsan64ui);
		helpers->log((char *)ffs1.c_str());
		helpers->log("got value: ");
		ffsanfranrush64 = sanfran64(ffsan64);
		ffsanfranrush64ui = sanfran64ui(ffsan64ui);

		if (FFBMode == 0)
		{
			if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64ui) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64ui) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64ui) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64ui) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			}
		}
	}
	else if (hWnd2 > NULL)
	{
	int ffsanfranrush64 = 0;
	int ffsanfranrush64ui = 0;
	{
		INT_PTR ff64 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x540, /* isRelativeOffset*/ false);
		INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x68, /* isRelativeOffset*/ false);
		UINT8 ffsan64 = helpers->ReadByte(ff464 + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit
		INT_PTR ff64ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x5A0, /* isRelativeOffset*/ false);
		INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x8, /* isRelativeOffset*/ false);
		UINT8 ffsan64ui = helpers->ReadByte(ff464ui + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit mameui
		std::string ffs1 = std::to_string(ffsan64);
		std::string ffs2 = std::to_string(ffsan64ui);
		helpers->log((char *)ffs1.c_str());
		helpers->log("got value: ");
		ffsanfranrush64 = sanfran64(ffsan64);
		ffsanfranrush64ui = sanfran64ui(ffsan64ui);

		if (FFBMode == 0)
		{
			if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64ui) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64ui) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush64ui) / 119.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush64ui) / 112.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			}
		}
	}
	if (hWnd3 > NULL)
	{
		INT_PTR ff204964 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ff2049164 = helpers->ReadIntPtr(ff204964 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264 = helpers->ReadIntPtr(ff2049164 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364 = helpers->ReadIntPtr(ff2049264 + 0x540, /* isRelativeOffset*/ false);
		UINT8 ff2049564 = helpers->ReadByte(ff2049364 + 0x7FC, /* isRelativeOffset */ false); //SanFranRush204964bit
		INT_PTR ff204964ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ff2049164ui = helpers->ReadIntPtr(ff204964ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264ui = helpers->ReadIntPtr(ff2049164ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364ui = helpers->ReadIntPtr(ff2049264ui + 0x7F0, /* isRelativeOffset*/ false);
		INT_PTR ff2049464ui = helpers->ReadIntPtr(ff2049364ui + 0x48, /* isRelativeOffset*/ false);
		UINT8 ff2049564ui = helpers->ReadByte(ff2049464ui + 0x62C, /* isRelativeOffset */ false); //SanFranRush204964bitmameUI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ff2049564);
		std::string ffs2 = std::to_string(ff2049564ui);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd7 > NULL)
	{
		int ffsanfranrush64 = 0;
		int ffsanfranrush64ui = 0;
		{
			INT_PTR ff64 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x540, /* isRelativeOffset*/ false);
			INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x68, /* isRelativeOffset*/ false);
			UINT8 ffsan64 = helpers->ReadByte(ff464 + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit
			INT_PTR ff64ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x5A0, /* isRelativeOffset*/ false);
			INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x8, /* isRelativeOffset*/ false);
			UINT8 ffsan64ui = helpers->ReadByte(ff464ui + 0x7DC, /* isRelativeOffset */ false); //SanFranRush64bit mameui
			std::string ffs1 = std::to_string(ffsan64);
			std::string ffs2 = std::to_string(ffsan64ui);
			helpers->log((char *)ffs1.c_str());
			helpers->log("got value: ");
			ffsanfranrush64 = sanfran64(ffsan64);
			ffsanfranrush64ui = sanfran64ui(ffsan64ui);

			if (FFBMode == 0)
			{
				if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64ui) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64ui) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffsanfranrush64 > 112) & (ffsanfranrush64 < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64 > 0) & (ffsanfranrush64 < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64ui > 112) & (ffsanfranrush64ui < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush64ui) / 119.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush64ui > 0) & (ffsanfranrush64ui < 114))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush64ui) / 112.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd4 > NULL)
	{
		int ffrave64 = 0;
		int ffraveui64 = 0;
		{
			INT_PTR ffrave640 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffrave641 = helpers->ReadIntPtr(ffrave640 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffrave642 = helpers->ReadIntPtr(ffrave641 + 0x28, /* isRelativeOffset*/ false);
			INT_PTR ffrave643 = helpers->ReadIntPtr(ffrave642 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffRaw64 = helpers->ReadByte(ffrave643 + 0x40, /* isRelativeOffset */ false); //Rave Racer 64bit
			INT_PTR ffraveui640 = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffraveui641 = helpers->ReadIntPtr(ffraveui640 + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffraveui642 = helpers->ReadIntPtr(ffraveui641 + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffraveui643 = helpers->ReadIntPtr(ffraveui642 + 0x2D8, /* isRelativeOffset*/ false);
			INT_PTR ffraveui644 = helpers->ReadIntPtr(ffraveui643 + 0x630, /* isRelativeOffset*/ false);
			UINT8 ffRawui64 = helpers->ReadByte(ffraveui644 + 0x40, /* isRelativeOffset */ false); //Rave Racer mameui 64bit
			ffrave64 = raveracer64(ffRaw64);
			ffraveui64 = raveracerui64(ffRawui64);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffrave64);
			std::string ffs2 = std::to_string(ffraveui64);
			helpers->log((char *)ffs1.c_str());
		}
		if (FFBMode == 0)
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
		else
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}

	if (hWnd5 > NULL)
	{
		int ffrave64 = 0;
		int ffraveui64 = 0;
		{
			INT_PTR ffrave640 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffrave641 = helpers->ReadIntPtr(ffrave640 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffrave642 = helpers->ReadIntPtr(ffrave641 + 0x28, /* isRelativeOffset*/ false);
			INT_PTR ffrave643 = helpers->ReadIntPtr(ffrave642 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffRaw64 = helpers->ReadByte(ffrave643 + 0x40, /* isRelativeOffset */ false); //Rave Racer 64bit
			INT_PTR ffraveui640 = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffraveui641 = helpers->ReadIntPtr(ffraveui640 + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffraveui642 = helpers->ReadIntPtr(ffraveui641 + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffraveui643 = helpers->ReadIntPtr(ffraveui642 + 0x2D8, /* isRelativeOffset*/ false);
			INT_PTR ffraveui644 = helpers->ReadIntPtr(ffraveui643 + 0x630, /* isRelativeOffset*/ false);
			UINT8 ffRawui64 = helpers->ReadByte(ffraveui644 + 0x40, /* isRelativeOffset */ false); //Rave Racer mameui 64bit
			ffrave64 = raveracer64(ffRaw64);
			ffraveui64 = raveracerui64(ffRawui64);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffrave64);
			std::string ffs2 = std::to_string(ffraveui64);
			helpers->log((char *)ffs1.c_str());
		}
		if (FFBMode == 0)
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
		else
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd6 > NULL)
	{
		int ffrave64 = 0;
		int ffraveui64 = 0;
		{
			INT_PTR ffrave640 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffrave641 = helpers->ReadIntPtr(ffrave640 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffrave642 = helpers->ReadIntPtr(ffrave641 + 0x28, /* isRelativeOffset*/ false);
			INT_PTR ffrave643 = helpers->ReadIntPtr(ffrave642 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffRaw64 = helpers->ReadByte(ffrave643 + 0x40, /* isRelativeOffset */ false); //Rave Racer 64bit
			INT_PTR ffraveui640 = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffraveui641 = helpers->ReadIntPtr(ffraveui640 + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffraveui642 = helpers->ReadIntPtr(ffraveui641 + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffraveui643 = helpers->ReadIntPtr(ffraveui642 + 0x2D8, /* isRelativeOffset*/ false);
			INT_PTR ffraveui644 = helpers->ReadIntPtr(ffraveui643 + 0x630, /* isRelativeOffset*/ false);
			UINT8 ffRawui64 = helpers->ReadByte(ffraveui644 + 0x40, /* isRelativeOffset */ false); //Rave Racer mameui 64bit
			ffrave64 = raveracer64(ffRaw64);
			ffraveui64 = raveracerui64(ffRawui64);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffrave64);
			std::string ffs2 = std::to_string(ffraveui64);
			helpers->log((char *)ffs1.c_str());
		}
		if (FFBMode == 0)
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
		else
		{
			if ((ffrave64 > 61) && (ffrave64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave64 > 0) && (ffrave64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 61) && (ffraveui64 < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffraveui64 > 0) && (ffraveui64 < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffraveui64) / 61.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd8 > NULL)
	{
		INT_PTR ff204964 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ff2049164 = helpers->ReadIntPtr(ff204964 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264 = helpers->ReadIntPtr(ff2049164 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364 = helpers->ReadIntPtr(ff2049264 + 0x540, /* isRelativeOffset*/ false);
		UINT8 ff2049564 = helpers->ReadByte(ff2049364 + 0x7FC, /* isRelativeOffset */ false); //SanFranRush204964bit
		INT_PTR ff204964ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ff2049164ui = helpers->ReadIntPtr(ff204964ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ff2049264ui = helpers->ReadIntPtr(ff2049164ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ff2049364ui = helpers->ReadIntPtr(ff2049264ui + 0x7F0, /* isRelativeOffset*/ false);
		INT_PTR ff2049464ui = helpers->ReadIntPtr(ff2049364ui + 0x48, /* isRelativeOffset*/ false);
		UINT8 ff2049564ui = helpers->ReadByte(ff2049464ui + 0x62C, /* isRelativeOffset */ false); //SanFranRush204964bitmameUI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ff2049564);
		std::string ffs2 = std::to_string(ff2049564ui);
		helpers->log((char *)ffs1.c_str());
		if (FFBMode == 0)
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff2049564 > 0x80) & (ff2049564 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564 > 0x00) & (ff2049564 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x80) & (ff2049564ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff2049564ui > 0x00) & (ff2049564ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff2049564ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd9 > NULL)
	{
		INT_PTR ffcal164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffcal264 = helpers->ReadIntPtr(ffcal164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364 = helpers->ReadIntPtr(ffcal264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464 = helpers->ReadIntPtr(ffcal364 + 0x570, /* isRelativeOffset*/ false);
		UINT8 ffcal664 = helpers->ReadByte(ffcal464 + 0x7E4, /* isRelativeOffset */ false); //CaliforniaSpeed64bit
		INT_PTR ffcal164ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffcal264ui = helpers->ReadIntPtr(ffcal164ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364ui = helpers->ReadIntPtr(ffcal264ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464ui = helpers->ReadIntPtr(ffcal364ui + 0x5A0, /* isRelativeOffset*/ false);
		UINT8 ffcal664ui = helpers->ReadByte(ffcal464ui + 0x7B4, /* isRelativeOffset */ false); //CaliforniaSpeedMameUI64
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffcal664);
		std::string ffs2 = std::to_string(ffcal664ui);
		helpers->log((char *)ffs1.c_str());
		if (FFBMode == 0)
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd10 > NULL)
	{
		INT_PTR ffcal164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffcal264 = helpers->ReadIntPtr(ffcal164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364 = helpers->ReadIntPtr(ffcal264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464 = helpers->ReadIntPtr(ffcal364 + 0x570, /* isRelativeOffset*/ false);
		UINT8 ffcal664 = helpers->ReadByte(ffcal464 + 0x7E4, /* isRelativeOffset */ false); //CaliforniaSpeed64bit
		INT_PTR ffcal164ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffcal264ui = helpers->ReadIntPtr(ffcal164ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364ui = helpers->ReadIntPtr(ffcal264ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464ui = helpers->ReadIntPtr(ffcal364ui + 0x5A0, /* isRelativeOffset*/ false);
		UINT8 ffcal664ui = helpers->ReadByte(ffcal464ui + 0x7B4, /* isRelativeOffset */ false); //CaliforniaSpeedMameUI64
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffcal664);
		std::string ffs2 = std::to_string(ffcal664ui);
		helpers->log((char *)ffs1.c_str());
		if (FFBMode == 0)
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd11 > NULL)
	{
		INT_PTR ffcal164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffcal264 = helpers->ReadIntPtr(ffcal164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364 = helpers->ReadIntPtr(ffcal264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464 = helpers->ReadIntPtr(ffcal364 + 0x570, /* isRelativeOffset*/ false);
		UINT8 ffcal664 = helpers->ReadByte(ffcal464 + 0x7E4, /* isRelativeOffset */ false); //CaliforniaSpeed64bit
		INT_PTR ffcal164ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffcal264ui = helpers->ReadIntPtr(ffcal164ui + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffcal364ui = helpers->ReadIntPtr(ffcal264ui + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffcal464ui = helpers->ReadIntPtr(ffcal364ui + 0x5A0, /* isRelativeOffset*/ false);
		UINT8 ffcal664ui = helpers->ReadByte(ffcal464ui + 0x7B4, /* isRelativeOffset */ false); //CaliforniaSpeedMameUI64
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffcal664);
		std::string ffs2 = std::to_string(ffcal664ui);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal664 > 0x80) & (ffcal664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664 > 0x00) & (ffcal664 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x80) & (ffcal664ui < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal664ui > 0x00) & (ffcal664ui < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal664ui) / 126.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd12 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd13 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd14 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd15 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd16 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd17 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd18 > NULL)
	{
		int ffcrusnwld64 = 0;
		int ffcrusnwldui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnwld64 = crusnwld64(ffcru664);
			ffcrusnwldui = crusnwldui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld64 > 110) & (ffcrusnwld64 < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld64) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld64 > 0) & (ffcrusnwld64 < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld64) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 110) & (ffcrusnwldui < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwldui) / 114.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwldui > 0) & (ffcrusnwldui < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwldui) / 110.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd19 > NULL)
	{
		int ffcrusnusa64 = 0;
		int ffcrusnusaui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnusa64 = crusnusa64(ffcru664);
			ffcrusnusaui = crusnusaui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd20 > NULL)
	{
		int ffcrusnusa64 = 0;
		int ffcrusnusaui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnusa64 = crusnusa64(ffcru664);
			ffcrusnusaui = crusnusaui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd21 > NULL)
	{
		int ffcrusnusa64 = 0;
		int ffcrusnusaui = 0;
		{
			INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
			INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, /* isRelativeOffset*/ false);
			INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, /* isRelativeOffset*/ false);
			INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, /* isRelativeOffset*/ false);
			UINT8 ffcru664 = helpers->ReadByte(ffcru564 + 0x54, /* isRelativeOffset */ false); //CrusnWld64bit
			INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
			INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, /* isRelativeOffset*/ false);
			INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, /* isRelativeOffset*/ false);
			INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, /* isRelativeOffset*/ false);
			UINT8 ffcru6ui = helpers->ReadByte(ffcru5ui + 0x7A4, /* isRelativeOffset */ false); //CrusnWldUI64
			ffcrusnusa64 = crusnusa64(ffcru664);
			ffcrusnusaui = crusnusaui(ffcru6ui);
			helpers->log("got value: ");
			std::string ffs1 = std::to_string(ffcru664);
			std::string ffs2 = std::to_string(ffcru6ui);
			helpers->log((char *)ffs1.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa64 > 104) & (ffcrusnusa64 < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa64) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa64 > 0) & (ffcrusnusa64 < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa64) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 104) & (ffcrusnusaui < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusaui) / 109.0;
					double percentLength = 100;
					triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusaui > 0) & (ffcrusnusaui < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusaui) / 104.0;
					double percentLength = 100;
					triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd22 > NULL)
	{
		INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, /* isRelativeOffset*/ false);
		INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, /* isRelativeOffset*/ false);
		UINT8 ffoff664 = helpers->ReadByte(ffoff564 + 0x7A4, /* isRelativeOffset */ false); //OffRoadChallenge64bit
		INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, /* isRelativeOffset*/ false);
		UINT8 ffoff664UI = helpers->ReadByte(ffoff464UI + 0x4CC, /* isRelativeOffset */ false); //OffRoadChallenge64UI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffoff664);
		std::string ffs2 = std::to_string(ffoff664UI);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd23 > NULL)
	{
		INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, /* isRelativeOffset*/ false);
		INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, /* isRelativeOffset*/ false);
		UINT8 ffoff664 = helpers->ReadByte(ffoff564 + 0x7A4, /* isRelativeOffset */ false); //OffRoadChallenge64bit
		INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, /* isRelativeOffset*/ false);
		UINT8 ffoff664UI = helpers->ReadByte(ffoff464UI + 0x4CC, /* isRelativeOffset */ false); //OffRoadChallenge64UI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffoff664);
		std::string ffs2 = std::to_string(ffoff664UI);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd24 > NULL)
	{
		INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, /* isRelativeOffset*/ false);
		INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, /* isRelativeOffset*/ false);
		UINT8 ffoff664 = helpers->ReadByte(ffoff564 + 0x7A4, /* isRelativeOffset */ false); //OffRoadChallenge64bit
		INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, /* isRelativeOffset*/ false);
		UINT8 ffoff664UI = helpers->ReadByte(ffoff464UI + 0x4CC, /* isRelativeOffset */ false); //OffRoadChallenge64UI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffoff664);
		std::string ffs2 = std::to_string(ffoff664UI);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd25 > NULL)
	{
		INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, /* isRelativeOffset*/ false);
		INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, /* isRelativeOffset*/ false);
		UINT8 ffoff664 = helpers->ReadByte(ffoff564 + 0x7A4, /* isRelativeOffset */ false); //OffRoadChallenge64bit
		INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, /* isRelativeOffset*/ false);
		UINT8 ffoff664UI = helpers->ReadByte(ffoff464UI + 0x4CC, /* isRelativeOffset */ false); //OffRoadChallenge64UI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffoff664);
		std::string ffs2 = std::to_string(ffoff664UI);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd26 > NULL)
	{
		INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, /* isRelativeOffset*/ true);
		INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, /* isRelativeOffset*/ false);
		INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, /* isRelativeOffset*/ false);
		UINT8 ffoff664 = helpers->ReadByte(ffoff564 + 0x7A4, /* isRelativeOffset */ false); //OffRoadChallenge64bit
		INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, /* isRelativeOffset*/ true);
		INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, /* isRelativeOffset*/ false);
		INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, /* isRelativeOffset*/ false);
		INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, /* isRelativeOffset*/ false);
		UINT8 ffoff664UI = helpers->ReadByte(ffoff464UI + 0x4CC, /* isRelativeOffset */ false); //OffRoadChallenge64UI
		helpers->log("got value: ");
		std::string ffs1 = std::to_string(ffoff664);
		std::string ffs2 = std::to_string(ffoff664UI);
		helpers->log((char *)ffs1.c_str());

		if (FFBMode == 0)
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffoff664 > 0x83) & (ffoff664 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664 > 0x00) & (ffoff664 < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x83) & (ffoff664UI < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffoff664UI > 0x00) & (ffoff664UI < 0x7D))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffoff664UI) / 124.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}

