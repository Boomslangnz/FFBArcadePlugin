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
#include "OldMame.h"
#include "math.h"

static int sanfran(int ffsan) {
	switch (ffsan) {

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

static int crusnwld(int ffcru) {
	switch (ffcru) {

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

static int crusnusa(int ffusa) {
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

static int raveracer(int ffRaw) {
	switch (ffRaw) {

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

UINT8 FFB;

void OldMame::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	
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

	char MameVersionChar[256];
	GetPrivateProfileStringA("Settings", "MameVersion", "", MameVersionChar, 256, ".\\FFBplugin.ini");
	std::string Mame019932bit("MAME019932bit");
	std::string Mame019964bit("MAME019964bit");
	std::string Mame019964bitHack("MAME019964bitHack");
	std::string Mame0199UI64bit("MAME0199UI64bit");
	std::string Mame020632bit("MAME020632bit");
	std::string Mame020664bit("MAME020664bit");
	std::string Mame0206UI64bit("MAME0206UI64bit");
	std::string mameversion(MameVersionChar);

	if ((hWnd > NULL) || (hWnd1 > NULL) || (hWnd2 > NULL) || (hWnd7 > NULL)) //Sfrush
	{
		int ffsanfranrush = 0;
		{
			if (mameversion.compare(Mame019932bit) == 0)
			{
				INT_PTR ff = helpers->ReadIntPtr(0x39B5D00, true);
				INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x708, false);
				INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x398, false);
				INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x34, false);
				INT_PTR ff4 = helpers->ReadIntPtr(ff3 + 0x24, false);
				FFB = helpers->ReadByte(ff4 + 0x5C0, false);
			}
			if (mameversion.compare(Mame019964bit) == 0)
			{
				INT_PTR ff64 = helpers->ReadIntPtr(0x0C5E4FE8, true);
				INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, false);
				INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x48, false);
				INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x668, false);
				INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x90, false);
				FFB = helpers->ReadByte(ff464 + 0x764, false);
			}
			if (mameversion.compare(Mame019964bitHack) == 0)
			{
				INT_PTR ff64hack = helpers->ReadIntPtr(0x0C50CFE8, true);
				INT_PTR ff164hack = helpers->ReadIntPtr(ff64hack + 0x48, false);
				INT_PTR ff264hack = helpers->ReadIntPtr(ff164hack + 0x48, false);
				INT_PTR ff364hack = helpers->ReadIntPtr(ff264hack + 0x48, false);
				INT_PTR ff464hack = helpers->ReadIntPtr(ff364hack + 0x90, false);
				FFB = helpers->ReadByte(ff464hack + 0x764, false);
			}
			if (mameversion.compare(Mame0199UI64bit) == 0)
			{
				INT_PTR ff64ui = helpers->ReadIntPtr(0x0C075FB8, true);
				INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x1A0, false);
				INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x10, false);
				INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x8, false);
				INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x18, false);
				FFB = helpers->ReadByte(ff464ui + 0x54, false);
			}
			if (mameversion.compare(Mame020632bit) == 0)
			{
				INT_PTR ff = helpers->ReadIntPtr(0x0E2B20A4, true);
				INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x134, false);
				INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x5D8, false);
				INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x564, false);
				FFB = helpers->ReadByte(ff3 + 0x550, false);
			}
			if (mameversion.compare(Mame020664bit) == 0)
			{
				INT_PTR ff64 = helpers->ReadIntPtr(0x0E198068, true);
				INT_PTR ff164 = helpers->ReadIntPtr(ff64 + 0x48, false);
				INT_PTR ff264 = helpers->ReadIntPtr(ff164 + 0x40, false);
				INT_PTR ff364 = helpers->ReadIntPtr(ff264 + 0x540, false);
				INT_PTR ff464 = helpers->ReadIntPtr(ff364 + 0x68, false);
				FFB = helpers->ReadByte(ff464 + 0x7DC, false);
			}
			if (mameversion.compare(Mame0206UI64bit) == 0)
			{
				INT_PTR ff64ui = helpers->ReadIntPtr(0x0DBCF058, true);
				INT_PTR ff164ui = helpers->ReadIntPtr(ff64ui + 0x48, false);
				INT_PTR ff264ui = helpers->ReadIntPtr(ff164ui + 0x40, false);
				INT_PTR ff364ui = helpers->ReadIntPtr(ff264ui + 0x5A0, false);
				INT_PTR ff464ui = helpers->ReadIntPtr(ff364ui + 0x8, false);
				FFB = helpers->ReadByte(ff464ui + 0x7DC, false);
			}

			ffsanfranrush = sanfran(FFB);

			if ((ffsanfranrush > 112)& (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush > 0)& (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
	}
	if ((hWnd4 > NULL) || (hWnd5 > NULL) || (hWnd6 > NULL)) //Rave Racer
	{
		int ffrave = 0;
		{
			if (mameversion.compare(Mame019932bit) == 0)
			{
				INT_PTR ffrave0 = helpers->ReadIntPtr(0x78D624C, true);
				INT_PTR ffrave1 = helpers->ReadIntPtr(ffrave0 + 0x0, false);
				INT_PTR ffrave2 = helpers->ReadIntPtr(ffrave1 + 0x34C, false);
				INT_PTR ffrave3 = helpers->ReadIntPtr(ffrave2 + 0x8, false);
				INT_PTR ffrave4 = helpers->ReadIntPtr(ffrave3 + 0x490, false);
				FFB = helpers->ReadByte(ffrave4 + 0x42, false);
			}
			if (mameversion.compare(Mame019964bit) == 0)
			{
				INT_PTR ffrave640 = helpers->ReadIntPtr(0x0C5E4FE8, true);
				INT_PTR ffrave641 = helpers->ReadIntPtr(ffrave640 + 0x90, false);
				INT_PTR ffrave642 = helpers->ReadIntPtr(ffrave641 + 0x8, false);
				INT_PTR ffrave643 = helpers->ReadIntPtr(ffrave642 + 0x130, false);
				INT_PTR ffrave644 = helpers->ReadIntPtr(ffrave643 + 0x720, false);
				FFB = helpers->ReadByte(ffrave644 + 0x42, false);
			}
			if (mameversion.compare(Mame0199UI64bit) == 0)
			{
				INT_PTR ffraveui640 = helpers->ReadIntPtr(0x0C075FB8, true);
				INT_PTR ffraveui641 = helpers->ReadIntPtr(ffraveui640 + 0x48, false);
				INT_PTR ffraveui642 = helpers->ReadIntPtr(ffraveui641 + 0x48, false);
				INT_PTR ffraveui643 = helpers->ReadIntPtr(ffraveui642 + 0x740, false);
				INT_PTR ffraveui644 = helpers->ReadIntPtr(ffraveui643 + 0x1F8, false);
				FFB = helpers->ReadByte(ffraveui644 + 0x42, false);
			}
			if (mameversion.compare(Mame020632bit) == 0)
			{
				INT_PTR ffrave0 = helpers->ReadIntPtr(0x02426C78, true);
				INT_PTR ffrave1 = helpers->ReadIntPtr(ffrave0 + 0x388, false);
				INT_PTR ffrave2 = helpers->ReadIntPtr(ffrave1 + 0x1A0, false);
				INT_PTR ffrave3 = helpers->ReadIntPtr(ffrave2 + 0x358, false);
				FFB = helpers->ReadByte(ffrave3 + 0x40, false);
			}
			if (mameversion.compare(Mame020664bit) == 0)
			{
				INT_PTR ffrave640 = helpers->ReadIntPtr(0x0E198068, true);
				INT_PTR ffrave641 = helpers->ReadIntPtr(ffrave640 + 0x2E8, false);
				INT_PTR ffrave642 = helpers->ReadIntPtr(ffrave641 + 0x28, false);
				INT_PTR ffrave643 = helpers->ReadIntPtr(ffrave642 + 0x0, false);
				FFB = helpers->ReadByte(ffrave643 + 0x40, false);
			}
			if (mameversion.compare(Mame0206UI64bit) == 0)
			{
				INT_PTR ffraveui640 = helpers->ReadIntPtr(0x0DBCF058, true);
				INT_PTR ffraveui641 = helpers->ReadIntPtr(ffraveui640 + 0x48, false);
				INT_PTR ffraveui642 = helpers->ReadIntPtr(ffraveui641 + 0x40, false);
				INT_PTR ffraveui643 = helpers->ReadIntPtr(ffraveui642 + 0x2D8, false);
				INT_PTR ffraveui644 = helpers->ReadIntPtr(ffraveui643 + 0x630, false);
				FFB = helpers->ReadByte(ffraveui644 + 0x40, false);
			}

			ffrave = raveracer(FFB);
		}
		if ((ffrave > 61) && (ffrave < 124))
		{
			helpers->log("moving wheel right");
			double percentForce = (124 - ffrave) / 61.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ffrave > 0) && (ffrave < 62))
		{
			helpers->log("moving wheel left");
			double percentForce = (ffrave) / 61.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
	if ((hWnd3 > NULL) || (hWnd8 > NULL) || (hWnds > NULL)) //Sfrush2049
	{
		if (mameversion.compare(Mame019932bit) == 0)
		{
			INT_PTR ff2049 = helpers->ReadIntPtr(0x2956BA8, true);
			INT_PTR ff20491 = helpers->ReadIntPtr(ff2049 + 0x160, false);
			INT_PTR ff20492 = helpers->ReadIntPtr(ff20491 + 0x30C, false);
			INT_PTR ff20493 = helpers->ReadIntPtr(ff20492 + 0x38C, false);
			INT_PTR ff20494 = helpers->ReadIntPtr(ff20493 + 0xB0, false);
			FFB = helpers->ReadByte(ff20494 + 0x4C8, false);
		}
		if (mameversion.compare(Mame019964bit) == 0)
		{
			INT_PTR ff204964 = helpers->ReadIntPtr(0x0C5E4FE8, true);
			INT_PTR ff2049164 = helpers->ReadIntPtr(ff204964 + 0x48, false);
			INT_PTR ff2049264 = helpers->ReadIntPtr(ff2049164 + 0x48, false);
			INT_PTR ff2049364 = helpers->ReadIntPtr(ff2049264 + 0x310, false);
			INT_PTR ff2049464 = helpers->ReadIntPtr(ff2049364 + 0x130, false);
			FFB = helpers->ReadByte(ff2049464 + 0x79C, false);
		}
		if (mameversion.compare(Mame0199UI64bit) == 0)
		{
			INT_PTR ff204964ui = helpers->ReadIntPtr(0x0CF9F7D0, true);
			INT_PTR ff2049164ui = helpers->ReadIntPtr(ff204964ui + 0x48, false);
			INT_PTR ff2049264ui = helpers->ReadIntPtr(ff2049164ui + 0x48, false);
			INT_PTR ff2049364ui = helpers->ReadIntPtr(ff2049264ui + 0x10, false);
			INT_PTR ff2049464ui = helpers->ReadIntPtr(ff2049364ui + 0x2D0, false);
			FFB = helpers->ReadByte(ff2049464ui + 0x79C, false);
		}
		if (mameversion.compare(Mame020632bit) == 0)
		{
			INT_PTR ff2049 = helpers->ReadIntPtr(0x02426C78, true);
			INT_PTR ff20491 = helpers->ReadIntPtr(ff2049 + 0x388, false);
			INT_PTR ff20492 = helpers->ReadIntPtr(ff20491 + 0x6C4, false);
			FFB = helpers->ReadByte(ff20492 + 0x7C, false);
		}
		if (mameversion.compare(Mame020664bit) == 0)
		{
			INT_PTR ff204964 = helpers->ReadIntPtr(0x0E198068, true);
			INT_PTR ff2049164 = helpers->ReadIntPtr(ff204964 + 0x48, false);
			INT_PTR ff2049264 = helpers->ReadIntPtr(ff2049164 + 0x40, false);
			INT_PTR ff2049364 = helpers->ReadIntPtr(ff2049264 + 0x540, false);
			FFB = helpers->ReadByte(ff2049364 + 0x7FC, false);
		}
		if (mameversion.compare(Mame0206UI64bit) == 0)
		{
			INT_PTR ff204964ui = helpers->ReadIntPtr(0x0DBCF058, true);
			INT_PTR ff2049164ui = helpers->ReadIntPtr(ff204964ui + 0x48, false);
			INT_PTR ff2049264ui = helpers->ReadIntPtr(ff2049164ui + 0x40, false);
			INT_PTR ff2049364ui = helpers->ReadIntPtr(ff2049264ui + 0x7F0, false);
			INT_PTR ff2049464ui = helpers->ReadIntPtr(ff2049364ui + 0x48, false);
			FFB = helpers->ReadByte(ff2049464ui + 0x62C, false);
		}

		if ((FFB > 0x80)& (FFB < 0x100))
		{
			helpers->log("moving wheel left");
			double percentForce = (255 - FFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((FFB > 0x00)& (FFB < 0x80))
		{
			helpers->log("moving wheel right");
			double percentForce = (FFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	if ((hWnd9 > NULL) || (hWnd10 > NULL) || (hWnd11 > NULL)) //CaliforniaSpeed
	{
		if (mameversion.compare(Mame019932bit) == 0)
		{
			INT_PTR ffcal1 = helpers->ReadIntPtr(0xC61E0A4, true);
			INT_PTR ffcal2 = helpers->ReadIntPtr(ffcal1 + 0x118, false);
			INT_PTR ffcal3 = helpers->ReadIntPtr(ffcal2 + 0x1C, false);
			INT_PTR ffcal4 = helpers->ReadIntPtr(ffcal3 + 0x7D4, false);
			INT_PTR ffcal5 = helpers->ReadIntPtr(ffcal4 + 0x0, false);
			FFB = helpers->ReadByte(ffcal5 + 0x598, false);
		}
		if (mameversion.compare(Mame019964bit) == 0)
		{
			INT_PTR ffcal164 = helpers->ReadIntPtr(0x0C5E4FE8, true);
			INT_PTR ffcal264 = helpers->ReadIntPtr(ffcal164 + 0x48, false);
			INT_PTR ffcal364 = helpers->ReadIntPtr(ffcal264 + 0x48, false);
			INT_PTR ffcal464 = helpers->ReadIntPtr(ffcal364 + 0x310, false);
			INT_PTR ffcal564 = helpers->ReadIntPtr(ffcal464 + 0x398, false);
			FFB = helpers->ReadByte(ffcal564 + 0x5AC, false);
		}
		if (mameversion.compare(Mame0199UI64bit) == 0)
		{
			INT_PTR ffcal164ui = helpers->ReadIntPtr(0x0C075FB8, true);
			INT_PTR ffcal264ui = helpers->ReadIntPtr(ffcal164ui + 0x48, false);
			INT_PTR ffcal364ui = helpers->ReadIntPtr(ffcal264ui + 0x48, false);
			INT_PTR ffcal464ui = helpers->ReadIntPtr(ffcal364ui + 0x140, false);
			INT_PTR ffcal564ui = helpers->ReadIntPtr(ffcal464ui + 0x408, false);
			FFB = helpers->ReadByte(ffcal564ui + 0x5AC, false);
		}
		if (mameversion.compare(Mame020632bit) == 0)
		{
			INT_PTR ffcal1 = helpers->ReadIntPtr(0x02426C78, true);
			INT_PTR ffcal2 = helpers->ReadIntPtr(ffcal1 + 0x388, false);
			INT_PTR ffcal3 = helpers->ReadIntPtr(ffcal2 + 0x640, false);
			FFB = helpers->ReadByte(ffcal3 + 0x104, false);
		}
		if (mameversion.compare(Mame020664bit) == 0)
		{
			INT_PTR ffcal164 = helpers->ReadIntPtr(0x0E198068, true);
			INT_PTR ffcal264 = helpers->ReadIntPtr(ffcal164 + 0x48, false);
			INT_PTR ffcal364 = helpers->ReadIntPtr(ffcal264 + 0x40, false);
			INT_PTR ffcal464 = helpers->ReadIntPtr(ffcal364 + 0x570,  false);
			FFB = helpers->ReadByte(ffcal464 + 0x7E4, false);
		}
		if (mameversion.compare(Mame0206UI64bit) == 0)
		{
			INT_PTR ffcal164ui = helpers->ReadIntPtr(0x0DBCF058, true);
			INT_PTR ffcal264ui = helpers->ReadIntPtr(ffcal164ui + 0x48, false);
			INT_PTR ffcal364ui = helpers->ReadIntPtr(ffcal264ui + 0x40, false);
			INT_PTR ffcal464ui = helpers->ReadIntPtr(ffcal364ui + 0x5A0, false);
			FFB = helpers->ReadByte(ffcal464ui + 0x7B4, false);
		}

		if ((FFB > 0x80)& (FFB < 0x100))
		{
			helpers->log("moving wheel left");
			double percentForce = (255 - FFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((FFB > 0x00)& (FFB < 0x80))
		{
			helpers->log("moving wheel right");
			double percentForce = (FFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	if ((hWnd12 > NULL) || (hWnd13 > NULL) || (hWnd14 > NULL) || (hWnd15 > NULL) || (hWnd16 > NULL) || (hWnd17 > NULL) || (hWnd18 > NULL))
	{
		int ffcrusnwld = 0;
		{
			if (mameversion.compare(Mame019932bit) == 0)
			{
				INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, true);
				INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, false);
				INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, false);
				INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, false);
				INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, false);
				FFB = helpers->ReadByte(ffcru5 + 0x5A0, false);
			}
			if (mameversion.compare(Mame019964bit) == 0)
			{
				INT_PTR ffcru164 = helpers->ReadIntPtr(0x0C5E4FE8, true);
				INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0x48, false);
				INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x48, false);
				INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0xF0, false);
				INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x1F0, false);
				FFB = helpers->ReadByte(ffcru564 + 0x774, false);
			}
			if (mameversion.compare(Mame0199UI64bit) == 0)
			{
				INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0C075FB8, true);
				INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, false);
				INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x48, false);
				INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0xF0, false);
				INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x1F0, false);
				FFB = helpers->ReadByte(ffcru5ui + 0x774, false);
			}
			if (mameversion.compare(Mame020632bit) == 0)
			{
				INT_PTR ffcru1 = helpers->ReadIntPtr(0x02426C78, true);
				INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x290, false);
				INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x650, false);
				FFB = helpers->ReadByte(ffcru3 + 0x248, false);
			}
			if (mameversion.compare(Mame020664bit) == 0)
			{
				INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, true);
				INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, false);
				INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, false);
				INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, false);
				INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, false);
				FFB = helpers->ReadByte(ffcru564 + 0x54, false);
			}
			if (mameversion.compare(Mame0206UI64bit) == 0)
			{
				INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, true);
				INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, false);
				INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, false);
				INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, false);
				INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, false);
				FFB = helpers->ReadByte(ffcru5ui + 0x7A4, false);
			}
			
			ffcrusnwld = crusnwld(FFB);

			if ((ffcrusnwld > 110)& (ffcrusnwld < 226))
			{
				helpers->log("moving wheel left");
				double percentForce = (225 - FFB) / 114.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcrusnwld > 0)& (ffcrusnwld < 111))
			{
				helpers->log("moving wheel right");
				double percentForce = (FFB) / 110.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
	}
	if ((hWnd19 > NULL) || (hWnd20 > NULL) || (hWnd21 > NULL)) //Crusn USA
	{
		int ffcrusnusa = 0;
		{
			if (mameversion.compare(Mame019932bit) == 0)
			{
				INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, true);
				INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, false);
				INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, false);
				INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, false);
				INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, false);
				FFB = helpers->ReadByte(ffcru5 + 0x5A0, false);
			}
			if (mameversion.compare(Mame019964bit) == 0)
			{
				INT_PTR ffcru164 = helpers->ReadIntPtr(0x0C5E4FE8, true);
				INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0x48, false);
				INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x48, false);
				INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0xF0, false);
				INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x1F0, false);
				FFB = helpers->ReadByte(ffcru564 + 0x774, false);
			}
			if (mameversion.compare(Mame0199UI64bit) == 0)
			{
				INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0C075FB8, true);
				INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, false);
				INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x48, false);
				INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0xF0, false);
				INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x1F0, false);
				FFB = helpers->ReadByte(ffcru5ui + 0x774, false);
			}
			if (mameversion.compare(Mame020632bit) == 0)
			{
				INT_PTR ffcru1 = helpers->ReadIntPtr(0x02426C78, true);
				INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x290, false);
				INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x650, false);
				FFB = helpers->ReadByte(ffcru3 + 0x248, false);
			}
			if (mameversion.compare(Mame020664bit) == 0)
			{
				INT_PTR ffcru164 = helpers->ReadIntPtr(0x0E198068, true);
				INT_PTR ffcru264 = helpers->ReadIntPtr(ffcru164 + 0xB8, false);
				INT_PTR ffcru364 = helpers->ReadIntPtr(ffcru264 + 0x8, false);
				INT_PTR ffcru464 = helpers->ReadIntPtr(ffcru364 + 0x0, false);
				INT_PTR ffcru564 = helpers->ReadIntPtr(ffcru464 + 0x0, false);
				FFB = helpers->ReadByte(ffcru564 + 0x54, false);
			}
			if (mameversion.compare(Mame0206UI64bit) == 0)
			{
				INT_PTR ffcru1ui = helpers->ReadIntPtr(0x0DBCF058, true);
				INT_PTR ffcru2ui = helpers->ReadIntPtr(ffcru1ui + 0x48, false);
				INT_PTR ffcru3ui = helpers->ReadIntPtr(ffcru2ui + 0x40, false);
				INT_PTR ffcru4ui = helpers->ReadIntPtr(ffcru3ui + 0x10, false);
				INT_PTR ffcru5ui = helpers->ReadIntPtr(ffcru4ui + 0x2B8, false);
				FFB = helpers->ReadByte(ffcru5ui + 0x7A4, false);
			}
					
			ffcrusnusa = crusnusa(FFB);
			
			if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
			{
				helpers->log("moving wheel left");
				double percentForce = (215 - FFB) / 110.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
			{
				helpers->log("moving wheel right");
				double percentForce = (FFB) / 104.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
	}				
	if ((hWnd22 > NULL) || (hWnd23 > NULL) || (hWnd24 > NULL) || (hWnd25 > NULL) || (hWnd26 > NULL)) //OffRoadChallenge
	{
		if (mameversion.compare(Mame019932bit) == 0)
		{
			INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, true);
			INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, false);
			INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, false);
			INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, false);
			INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, false);
			FFB = helpers->ReadByte(ffoff5 + 0x3C, false); 
		}
		if (mameversion.compare(Mame019964bit) == 0)
		{
			INT_PTR ffoff164 = helpers->ReadIntPtr(0x0C5E4FE8, true);
			INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0xB8, false);
			INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x8, false);
			INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x0, false);
			INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x0, false);
			FFB = helpers->ReadByte(ffoff564 + 0x54, false);
		}
		if (mameversion.compare(Mame0199UI64bit) == 0)
		{
			INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0C075FB8, true);
			INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0xB8, false);
			INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x8, false);
			INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x40, false);
			INT_PTR ffoff564UI = helpers->ReadIntPtr(ffoff464UI + 0x0, false);
			FFB = helpers->ReadByte(ffoff564UI + 0x54, false);
		}
		if (mameversion.compare(Mame020632bit) == 0)
		{
			INT_PTR ffoff1 = helpers->ReadIntPtr(0x02426C78, true);
			INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x290, false);
			INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x650, false);
			FFB = helpers->ReadByte(ffoff3 + 0x248, false);
		}
		if (mameversion.compare(Mame020664bit) == 0)
		{
			INT_PTR ffoff164 = helpers->ReadIntPtr(0x0E198068, true);
			INT_PTR ffoff264 = helpers->ReadIntPtr(ffoff164 + 0x48, false);
			INT_PTR ffoff364 = helpers->ReadIntPtr(ffoff264 + 0x40, false);
			INT_PTR ffoff464 = helpers->ReadIntPtr(ffoff364 + 0x120, false);
			INT_PTR ffoff564 = helpers->ReadIntPtr(ffoff464 + 0x1A8, false);
			FFB = helpers->ReadByte(ffoff564 + 0x7A4, false);
		}
		if (mameversion.compare(Mame0206UI64bit) == 0)
		{
			INT_PTR ffoff164UI = helpers->ReadIntPtr(0x0DBCF058, true);
			INT_PTR ffoff264UI = helpers->ReadIntPtr(ffoff164UI + 0x48, false);
			INT_PTR ffoff364UI = helpers->ReadIntPtr(ffoff264UI + 0x40, false);
			INT_PTR ffoff464UI = helpers->ReadIntPtr(ffoff364UI + 0x588, false);
			FFB = helpers->ReadByte(ffoff464UI + 0x4CC, false);
		}

		if ((FFB > 0x83)& (FFB < 0x100))
		{
			helpers->log("moving wheel left");
			double percentForce = (255 - FFB) / 124.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((FFB > 0x00)& (FFB < 0x7D))
		{
			helpers->log("moving wheel right");
			double percentForce = (FFB) / 124.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
}		