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
#include "Mame0199.h"
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

void Mame0199::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
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
		INT_PTR ff2049 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ff20491 = helpers->ReadIntPtr(ff2049 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ff20492 = helpers->ReadIntPtr(ff20491 + 0x34, /* isRelativeOffset*/ false);
		INT_PTR ff20493 = helpers->ReadIntPtr(ff20492 + 0x18, /* isRelativeOffset*/ false);
		INT_PTR ff20494 = helpers->ReadIntPtr(ff20493 + 0x54, /* isRelativeOffset*/ false);
		UINT8 ff20495 = helpers->ReadByte(ff20494 + 0x4E8, /* isRelativeOffset */ false); //SanFranRush2049
		helpers->log("got value: ");
		std::string ffs = std::to_string(ff20495);
		helpers->log((char *)ffs.c_str());

		if (FFBMode == 0)
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd > NULL)
	{
		int ffsanfranrush = 0;
		{
			INT_PTR ff = helpers->ReadIntPtr(0x0096D760, /* isRelativeOffset*/ true);
			INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x34C, /* isRelativeOffset*/ false);
			INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x34, /* isRelativeOffset*/ false);
			INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x18, /* isRelativeOffset*/ false);
			INT_PTR ff4 = helpers->ReadIntPtr(ff3 + 0x1C, /* isRelativeOffset*/ false);
			UINT8 ffsan = helpers->ReadByte(ff4 + 0x70C, /* isRelativeOffset */ false); //SanFranRush
			std::string ffs = std::to_string(ffsan);
			helpers->log((char *)ffs.c_str());
			helpers->log("got value: ");
			ffsanfranrush = sanfran(ffsan);

			if (FFBMode == 0)
			{
				if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush) / 119.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush) / 112.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{ 
			if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}
	else if (hWnd1 > NULL)
	{
	int ffsanfranrush = 0;
	{
		INT_PTR ff = helpers->ReadIntPtr(0x0096D760, /* isRelativeOffset*/ true);
		INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x34C, /* isRelativeOffset*/ false);
		INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x34, /* isRelativeOffset*/ false);
		INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x18, /* isRelativeOffset*/ false);
		INT_PTR ff4 = helpers->ReadIntPtr(ff3 + 0x1C, /* isRelativeOffset*/ false);
		UINT8 ffsan = helpers->ReadByte(ff4 + 0x70C, /* isRelativeOffset */ false); //SanFranRush
		std::string ffs = std::to_string(ffsan);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		ffsanfranrush = sanfran(ffsan);

		if (FFBMode == 0)
		{
			if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}
	else if (hWnd2 > NULL)
	{
		int ffsanfranrush = 0;
		{
			INT_PTR ff = helpers->ReadIntPtr(0x0096D760, /* isRelativeOffset*/ true);
			INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x34C, /* isRelativeOffset*/ false);
			INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x34, /* isRelativeOffset*/ false);
			INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x18, /* isRelativeOffset*/ false);
			INT_PTR ff4 = helpers->ReadIntPtr(ff3 + 0x1C, /* isRelativeOffset*/ false);
			UINT8 ffsan = helpers->ReadByte(ff4 + 0x70C, /* isRelativeOffset */ false); //SanFranRush
			std::string ffs = std::to_string(ffsan);
			helpers->log((char *)ffs.c_str());
			helpers->log("got value: ");
			ffsanfranrush = sanfran(ffsan);

			if (FFBMode == 0)
			{
				if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush) / 119.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush) / 112.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
				{
					helpers->log("moving wheel left");
					double percentForce = (233 - ffsanfranrush) / 119.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffsanfranrush) / 112.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd3 > NULL)
	{
		INT_PTR ff2049 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ff20491 = helpers->ReadIntPtr(ff2049 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ff20492 = helpers->ReadIntPtr(ff20491 + 0x34, /* isRelativeOffset*/ false);
		INT_PTR ff20493 = helpers->ReadIntPtr(ff20492 + 0x18, /* isRelativeOffset*/ false);
		INT_PTR ff20494 = helpers->ReadIntPtr(ff20493 + 0x54, /* isRelativeOffset*/ false);
		UINT8 ff20495 = helpers->ReadByte(ff20494 + 0x4E8, /* isRelativeOffset */ false); //SanFranRush2049
		helpers->log("got value: ");
		std::string ffs = std::to_string(ff20495);
		helpers->log((char *)ffs.c_str());

		if (FFBMode == 0)
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd7 > NULL)
	{
	int ffsanfranrush = 0;
	{
		INT_PTR ff = helpers->ReadIntPtr(0x0096D760, /* isRelativeOffset*/ true);
		INT_PTR ff1 = helpers->ReadIntPtr(ff + 0x34C, /* isRelativeOffset*/ false);
		INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x34, /* isRelativeOffset*/ false);
		INT_PTR ff3 = helpers->ReadIntPtr(ff2 + 0x18, /* isRelativeOffset*/ false);
		INT_PTR ff4 = helpers->ReadIntPtr(ff3 + 0x1C, /* isRelativeOffset*/ false);
		UINT8 ffsan = helpers->ReadByte(ff4 + 0x70C, /* isRelativeOffset */ false); //SanFranRush
		std::string ffs = std::to_string(ffsan);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		ffsanfranrush = sanfran(ffsan);

		if (FFBMode == 0)
		{
			if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffsanfranrush > 112) & (ffsanfranrush < 233))
			{
				helpers->log("moving wheel left");
				double percentForce = (233 - ffsanfranrush) / 119.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffsanfranrush > 0) & (ffsanfranrush < 113))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffsanfranrush) / 112.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}
	if (hWnd4 > NULL)
	{
		int ffrave = 0;
		{
			INT_PTR ffrave0 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
			INT_PTR ffrave1 = helpers->ReadIntPtr(ffrave0 + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffrave2 = helpers->ReadIntPtr(ffrave1 + 0x90, /* isRelativeOffset*/ false);
			INT_PTR ffrave3 = helpers->ReadIntPtr(ffrave2 + 0x18, /* isRelativeOffset*/ false);
			INT_PTR ffrave4 = helpers->ReadIntPtr(ffrave3 + 0x3D8, /* isRelativeOffset*/ false);
			UINT8 ffRaw = helpers->ReadByte(ffrave4 + 0x42, /* isRelativeOffset */ false); //Rave Racer 32bit
			ffrave = raveracer(ffRaw);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffrave);
			helpers->log((char *)ffs.c_str());
		}
		if (FFBMode == 0)
		{
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
		else
		{
			if ((ffrave > 61) && (ffrave < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave > 0) && (ffrave < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}

	if (hWnd5 > NULL)
	{
		int ffrave = 0;
		{
			INT_PTR ffrave0 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
			INT_PTR ffrave1 = helpers->ReadIntPtr(ffrave0 + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffrave2 = helpers->ReadIntPtr(ffrave1 + 0x90, /* isRelativeOffset*/ false);
			INT_PTR ffrave3 = helpers->ReadIntPtr(ffrave2 + 0x18, /* isRelativeOffset*/ false);
			INT_PTR ffrave4 = helpers->ReadIntPtr(ffrave3 + 0x3D8, /* isRelativeOffset*/ false);
			UINT8 ffRaw = helpers->ReadByte(ffrave4 + 0x42, /* isRelativeOffset */ false); //Rave Racer 32bit

			ffrave = raveracer(ffRaw);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffrave);
			helpers->log((char *)ffs.c_str());
		}
		if (FFBMode == 0)
		{
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
		else
		{
			if ((ffrave > 61) && (ffrave < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave > 0) && (ffrave < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd6 > NULL)
	{
		int ffrave = 0;
		{
			INT_PTR ffrave0 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
			INT_PTR ffrave1 = helpers->ReadIntPtr(ffrave0 + 0x10, /* isRelativeOffset*/ false);
			INT_PTR ffrave2 = helpers->ReadIntPtr(ffrave1 + 0x90, /* isRelativeOffset*/ false);
			INT_PTR ffrave3 = helpers->ReadIntPtr(ffrave2 + 0x18, /* isRelativeOffset*/ false);
			INT_PTR ffrave4 = helpers->ReadIntPtr(ffrave3 + 0x3D8, /* isRelativeOffset*/ false);
			UINT8 ffRaw = helpers->ReadByte(ffrave4 + 0x42, /* isRelativeOffset */ false); //Rave Racer 32bit

			ffrave = raveracer(ffRaw);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffrave);
			helpers->log((char *)ffs.c_str());
		}
		if (FFBMode == 0)
		{
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
		else
		{
			if ((ffrave > 61) && (ffrave < 124))
			{
				helpers->log("moving wheel right");
				double percentForce = (124 - ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ffrave > 0) && (ffrave < 62))
			{
				helpers->log("moving wheel left");
				double percentForce = (ffrave) / 61.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd8 > NULL)
	{
		INT_PTR ff2049 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ff20491 = helpers->ReadIntPtr(ff2049 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ff20492 = helpers->ReadIntPtr(ff20491 + 0x34, /* isRelativeOffset*/ false);
		INT_PTR ff20493 = helpers->ReadIntPtr(ff20492 + 0x18, /* isRelativeOffset*/ false);
		INT_PTR ff20494 = helpers->ReadIntPtr(ff20493 + 0x54, /* isRelativeOffset*/ false);
		UINT8 ff20495 = helpers->ReadByte(ff20494 + 0x4E8, /* isRelativeOffset */ false); //SanFranRush2049
		helpers->log("got value: ");
		std::string ffs = std::to_string(ff20495);
		helpers->log((char *)ffs.c_str());
		if (FFBMode == 0)
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff20495 > 0x80) & (ff20495 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff20495 > 0x00) & (ff20495 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff20495) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd9 > NULL)
	{
		INT_PTR ffcal1 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ffcal2 = helpers->ReadIntPtr(ffcal1 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ffcal3 = helpers->ReadIntPtr(ffcal2 + 0xE4, /* isRelativeOffset*/ false);
		INT_PTR ffcal4 = helpers->ReadIntPtr(ffcal3 + 0x4, /* isRelativeOffset*/ false);
		INT_PTR ffcal5 = helpers->ReadIntPtr(ffcal4 + 0xC, /* isRelativeOffset*/ false);
		UINT8 ffcal6 = helpers->ReadByte(ffcal5 + 0x1F8, /* isRelativeOffset */ false); //CaliforniaSpeed32bit
		helpers->log("got value: ");
		std::string ffs = std::to_string(ffcal6);
		helpers->log((char *)ffs.c_str());
		if (FFBMode == 0)
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd10 > NULL)
	{
		INT_PTR ffcal1 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ffcal2 = helpers->ReadIntPtr(ffcal1 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ffcal3 = helpers->ReadIntPtr(ffcal2 + 0xE4, /* isRelativeOffset*/ false);
		INT_PTR ffcal4 = helpers->ReadIntPtr(ffcal3 + 0x4, /* isRelativeOffset*/ false);
		INT_PTR ffcal5 = helpers->ReadIntPtr(ffcal4 + 0xC, /* isRelativeOffset*/ false);
		UINT8 ffcal6 = helpers->ReadByte(ffcal5 + 0x1F8, /* isRelativeOffset */ false); //CaliforniaSpeed32bit
		helpers->log("got value: ");
		std::string ffs = std::to_string(ffcal6);
		helpers->log((char *)ffs.c_str());
		if (FFBMode == 0)
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd11 > NULL)
	{
		INT_PTR ffcal1 = helpers->ReadIntPtr(0x078D624C, /* isRelativeOffset*/ true);
		INT_PTR ffcal2 = helpers->ReadIntPtr(ffcal1 + 0x10, /* isRelativeOffset*/ false);
		INT_PTR ffcal3 = helpers->ReadIntPtr(ffcal2 + 0xE4, /* isRelativeOffset*/ false);
		INT_PTR ffcal4 = helpers->ReadIntPtr(ffcal3 + 0x4, /* isRelativeOffset*/ false);
		INT_PTR ffcal5 = helpers->ReadIntPtr(ffcal4 + 0xC, /* isRelativeOffset*/ false);
		UINT8 ffcal6 = helpers->ReadByte(ffcal5 + 0x1F8, /* isRelativeOffset */ false); //CaliforniaSpeed32bit
		helpers->log("got value: ");
		std::string ffs = std::to_string(ffcal6);
		helpers->log((char *)ffs.c_str());

		if (FFBMode == 0)
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ffcal6 > 0x80) & (ffcal6 < 0x100))
			{
				helpers->log("moving wheel left");
				double percentForce = (255 - ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ffcal6 > 0x00) & (ffcal6 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (ffcal6) / 126.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd12 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd13 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd14 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd15 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd16 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd17 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd18 > NULL)
	{
		int ffcrusnwld = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnwld = crusnwld(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnwld > 110) & (ffcrusnwld < 226))
				{
					helpers->log("moving wheel left");
					double percentForce = (225 - ffcrusnwld) / 114.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnwld > 0) & (ffcrusnwld < 111))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnwld) / 110.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd19 > NULL)
	{
		int ffcrusnusa = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnusa = crusnusa(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd20 > NULL)
	{
		int ffcrusnusa = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnusa = crusnusa(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
	if (hWnd21 > NULL)
	{
		int ffcrusnusa = 0;
		{
			INT_PTR ffcru1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
			INT_PTR ffcru2 = helpers->ReadIntPtr(ffcru1 + 0x134, /* isRelativeOffset*/ false);
			INT_PTR ffcru3 = helpers->ReadIntPtr(ffcru2 + 0x2E8, /* isRelativeOffset*/ false);
			INT_PTR ffcru4 = helpers->ReadIntPtr(ffcru3 + 0x0, /* isRelativeOffset*/ false);
			INT_PTR ffcru5 = helpers->ReadIntPtr(ffcru4 + 0x20, /* isRelativeOffset*/ false);
			UINT8 ffcru6 = helpers->ReadByte(ffcru5 + 0x5A0, /* isRelativeOffset */ false); //CrusnWld32bit
			ffcrusnusa = crusnusa(ffcru6);
			helpers->log("got value: ");
			std::string ffs = std::to_string(ffcru6);
			helpers->log((char *)ffs.c_str());

			if (FFBMode == 0)
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
			else
			{
				if ((ffcrusnusa > 104) & (ffcrusnusa < 215))
				{
					helpers->log("moving wheel left");
					double percentForce = (214 - ffcrusnusa) / 109.0;
					double percentLength = 100;
					triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
				}
				else if ((ffcrusnusa > 0) & (ffcrusnusa < 105))
				{
					helpers->log("moving wheel right");
					double percentForce = (ffcrusnusa) / 104.0;
					double percentLength = 100;
					triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
				}
			}
		}
	}
			if (hWnd22 > NULL)
			{
				INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
				INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, /* isRelativeOffset*/ false);
				INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, /* isRelativeOffset*/ false);
				INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, /* isRelativeOffset*/ false);
				INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, /* isRelativeOffset*/ false);
				UINT8 ffoff6 = helpers->ReadByte(ffoff5 + 0x3C, /* isRelativeOffset */ false); //OffRoadChallenge32bit
				std::string ffs = std::to_string(ffoff6);
				helpers->log((char *)ffs.c_str());

				if (FFBMode == 0)
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
				}
				else
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
				}
			}
			if (hWnd23 > NULL)
			{
				INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
				INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, /* isRelativeOffset*/ false);
				INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, /* isRelativeOffset*/ false);
				INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, /* isRelativeOffset*/ false);
				INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, /* isRelativeOffset*/ false);
				UINT8 ffoff6 = helpers->ReadByte(ffoff5 + 0x3C, /* isRelativeOffset */ false); //OffRoadChallenge32bit
				helpers->log("got value: ");
				std::string ffs = std::to_string(ffoff6);
				helpers->log((char *)ffs.c_str());

				if (FFBMode == 0)
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
				}
				else
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
				}
			}
			if (hWnd24 > NULL)
			{
				INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
				INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, /* isRelativeOffset*/ false);
				INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, /* isRelativeOffset*/ false);
				INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, /* isRelativeOffset*/ false);
				INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, /* isRelativeOffset*/ false);
				UINT8 ffoff6 = helpers->ReadByte(ffoff5 + 0x3C, /* isRelativeOffset */ false); //OffRoadChallenge32bit
				helpers->log("got value: ");
				std::string ffs = std::to_string(ffoff6);
				helpers->log((char *)ffs.c_str());

				if (FFBMode == 0)
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
				}
				else
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
				}
			}
			if (hWnd25 > NULL)
			{
				INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
				INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, /* isRelativeOffset*/ false);
				INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, /* isRelativeOffset*/ false);
				INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, /* isRelativeOffset*/ false);
				INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, /* isRelativeOffset*/ false);
				UINT8 ffoff6 = helpers->ReadByte(ffoff5 + 0x3C, /* isRelativeOffset */ false); //OffRoadChallenge32bit
				helpers->log("got value: ");
				std::string ffs = std::to_string(ffoff6);
				helpers->log((char *)ffs.c_str());

				if (FFBMode == 0)
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
				}
				else
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
				}
			}
			if (hWnd26 > NULL)
			{
				INT_PTR ffoff1 = helpers->ReadIntPtr(0x0C61E0A4, /* isRelativeOffset*/ true);
				INT_PTR ffoff2 = helpers->ReadIntPtr(ffoff1 + 0x60, /* isRelativeOffset*/ false);
				INT_PTR ffoff3 = helpers->ReadIntPtr(ffoff2 + 0x4, /* isRelativeOffset*/ false);
				INT_PTR ffoff4 = helpers->ReadIntPtr(ffoff3 + 0x40, /* isRelativeOffset*/ false);
				INT_PTR ffoff5 = helpers->ReadIntPtr(ffoff4 + 0x0, /* isRelativeOffset*/ false);
				UINT8 ffoff6 = helpers->ReadByte(ffoff5 + 0x3C, /* isRelativeOffset */ false); //OffRoadChallenge32bit
				helpers->log("got value: ");
				std::string ffs = std::to_string(ffoff6);
				helpers->log((char *)ffs.c_str());

				if (FFBMode == 0)
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
				}
				else
				{
					if ((ffoff6 > 0x83) & (ffoff6 < 0x100))
					{
						helpers->log("moving wheel left");
						double percentForce = (255 - ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
					else if ((ffoff6 > 0x00) & (ffoff6 < 0x7D))
					{
						helpers->log("moving wheel right");
						double percentForce = (ffoff6) / 124.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
				}
			}
		}