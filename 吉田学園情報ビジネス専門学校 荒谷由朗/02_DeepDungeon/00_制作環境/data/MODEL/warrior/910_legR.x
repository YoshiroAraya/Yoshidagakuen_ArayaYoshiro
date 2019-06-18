xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 79;
 2.95485;-2.14207;4.13015;,
 4.17066;-2.25825;0.39228;,
 3.78728;-14.82430;0.31715;,
 0.80771;-2.30248;5.10275;,
 2.58058;-15.08127;6.04719;,
 2.38194;-2.34414;-5.48225;,
 1.15528;-15.20795;-6.71578;,
 3.33038;-14.95062;-5.34663;,
 -1.28073;-2.44015;5.27330;,
 -0.66089;-15.34122;7.54159;,
 0.11494;-2.68739;-5.30148;,
 -0.83064;-15.31628;-6.99039;,
 -3.39962;-3.01089;-3.88000;,
 -2.59847;-15.33303;7.09571;,
 -5.02330;-15.38215;7.10181;,
 -3.42822;-2.61799;5.27623;,
 -5.96197;-15.47563;0.69884;,
 -4.62571;-2.88704;0.72314;,
 3.61515;-2.56250;-3.26263;,
 -4.40648;-15.43059;-5.74129;,
 -0.15418;-11.13243;-0.10345;,
 0.54214;-11.13243;3.57134;,
 2.94504;-11.13243;2.00323;,
 0.25286;-19.03751;2.04472;,
 1.38419;-19.03751;1.17391;,
 1.70620;-19.03751;-2.06540;,
 -0.67976;-19.15140;-2.87724;,
 -0.99502;-11.13243;-4.54101;,
 -3.86625;-11.13243;0.59992;,
 -3.52890;-11.13243;-2.15792;,
 -2.60335;-19.03751;-1.24883;,
 3.55790;-11.13243;-0.80683;,
 1.62433;-19.03751;-0.46074;,
 -2.26788;-11.13243;2.99098;,
 -1.94011;-19.03751;0.21466;,
 2.23503;-11.13243;-3.25009;,
 -1.11861;-19.03751;1.64815;,
 -2.78296;-1.35714;1.61639;,
 -2.78585;-3.53023;1.61638;,
 -1.85589;-2.36832;2.89016;,
 -3.41037;-2.49447;-0.19988;,
 -2.92332;-4.30326;-0.19988;,
 -1.14791;-4.06872;2.73891;,
 -1.77534;-5.20605;0.92262;,
 -0.13671;-5.21944;1.70985;,
 -0.13741;-5.74457;-0.19988;,
 -1.77534;-5.20605;-1.32239;,
 -0.13671;-5.21944;-2.10962;,
 -1.14791;-4.06872;-3.13867;,
 -2.78585;-3.53023;-2.01615;,
 -1.85589;-2.36832;-3.28992;,
 -2.78296;-1.35714;-2.01616;,
 -2.91840;-0.60621;-0.19988;,
 -1.14323;-0.55259;2.73892;,
 -1.76776;0.48315;0.92262;,
 0.87781;-3.90430;2.73892;,
 -0.13271;-2.22845;3.43269;,
 1.50235;-4.94004;-1.32239;,
 1.50235;-4.94004;0.92262;,
 -0.13271;-2.22845;-3.83245;,
 0.87781;-3.90430;-3.13869;,
 -1.76776;0.48315;-1.32239;,
 -1.14323;-0.55259;-3.13869;,
 0.88250;-0.38816;2.73891;,
 1.59047;-2.08856;2.89016;,
 2.51755;-3.09976;1.61639;,
 2.65298;-3.85069;-0.19988;,
 2.51755;-3.09976;-2.01616;,
 1.59047;-2.08856;-3.28992;,
 0.88250;-0.38816;-3.13867;,
 -0.12871;0.76255;-2.10962;,
 -0.12801;1.28769;-0.19988;,
 -0.12871;0.76255;1.70985;,
 2.52043;-0.92669;1.61638;,
 1.50993;0.74915;0.92262;,
 3.14496;-1.96242;-0.19988;,
 2.52043;-0.92669;-2.01615;,
 1.50993;0.74915;-1.32239;,
 2.65791;-0.15362;-0.19988;;
 
 166;
 3;0,1,2;,
 3;3,0,4;,
 3;5,6,7;,
 3;8,3,9;,
 3;10,11,6;,
 3;11,10,12;,
 3;13,14,15;,
 3;14,16,17;,
 3;3,18,1;,
 3;16,19,12;,
 3;18,7,2;,
 3;0,2,4;,
 3;3,4,9;,
 3;5,7,18;,
 3;8,9,13;,
 3;10,6,5;,
 3;11,12,19;,
 3;13,15,8;,
 3;14,17,15;,
 3;18,10,5;,
 3;10,17,12;,
 3;17,8,15;,
 3;8,10,3;,
 3;0,3,1;,
 3;18,3,10;,
 3;17,10,8;,
 3;16,12,17;,
 3;18,2,1;,
 3;2,1,0;,
 3;4,0,3;,
 3;7,6,5;,
 3;9,3,8;,
 3;6,11,10;,
 3;12,10,11;,
 3;15,14,13;,
 3;17,16,14;,
 3;1,18,3;,
 3;12,19,16;,
 3;2,7,18;,
 3;4,2,0;,
 3;9,4,3;,
 3;18,7,5;,
 3;13,9,8;,
 3;5,6,10;,
 3;19,12,11;,
 3;8,15,13;,
 3;15,17,14;,
 3;5,10,18;,
 3;12,17,10;,
 3;15,8,17;,
 3;3,10,8;,
 3;1,3,0;,
 3;10,3,18;,
 3;8,10,17;,
 3;17,12,16;,
 3;1,2,18;,
 3;20,21,22;,
 3;21,23,24;,
 3;25,26,27;,
 3;28,29,30;,
 3;31,32,25;,
 3;22,24,32;,
 3;33,28,34;,
 3;35,27,20;,
 3;29,28,20;,
 3;30,29,27;,
 3;21,33,36;,
 3;20,28,33;,
 3;32,34,26;,
 3;20,22,31;,
 3;21,24,22;,
 3;25,27,35;,
 3;28,30,34;,
 3;31,25,35;,
 3;22,32,31;,
 3;33,34,36;,
 3;35,20,31;,
 3;29,20,27;,
 3;30,27,26;,
 3;21,36,23;,
 3;20,33,21;,
 3;34,32,36;,
 3;23,36,24;,
 3;32,26,25;,
 3;26,34,30;,
 3;36,32,24;,
 3;37,38,39;,
 3;40,38,37;,
 3;40,41,38;,
 3;42,43,44;,
 3;38,43,42;,
 3;38,41,43;,
 3;45,46,47;,
 3;43,46,45;,
 3;43,41,46;,
 3;48,49,50;,
 3;46,49,48;,
 3;46,41,49;,
 3;51,40,52;,
 3;49,40,51;,
 3;49,41,40;,
 3;53,37,39;,
 3;54,37,53;,
 3;54,52,37;,
 3;55,42,44;,
 3;56,42,55;,
 3;56,39,42;,
 3;57,45,47;,
 3;58,45,57;,
 3;58,44,45;,
 3;59,48,50;,
 3;60,48,59;,
 3;60,47,48;,
 3;61,51,52;,
 3;62,51,61;,
 3;62,50,51;,
 3;63,56,64;,
 3;53,56,63;,
 3;53,39,56;,
 3;65,58,66;,
 3;55,58,65;,
 3;55,44,58;,
 3;67,60,68;,
 3;57,60,67;,
 3;57,47,60;,
 3;69,62,70;,
 3;59,62,69;,
 3;59,50,62;,
 3;71,54,72;,
 3;61,54,71;,
 3;61,52,54;,
 3;73,63,64;,
 3;74,63,73;,
 3;74,72,63;,
 3;75,65,66;,
 3;73,65,75;,
 3;73,64,65;,
 3;76,67,68;,
 3;75,67,76;,
 3;75,66,67;,
 3;77,74,78;,
 3;71,74,77;,
 3;71,72,74;,
 3;77,69,70;,
 3;76,69,77;,
 3;76,68,69;,
 3;52,40,37;,
 3;39,38,42;,
 3;44,43,45;,
 3;47,46,48;,
 3;50,49,51;,
 3;72,54,53;,
 3;64,56,55;,
 3;66,58,57;,
 3;68,60,59;,
 3;70,62,61;,
 3;72,53,63;,
 3;64,55,65;,
 3;66,57,67;,
 3;68,59,69;,
 3;70,61,71;,
 3;78,74,73;,
 3;78,73,75;,
 3;78,75,76;,
 3;70,71,77;,
 3;78,76,77;;
 
 MeshMaterialList {
  2;
  166;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.188235;0.062745;0.031373;1.000000;;
   0.500000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.196078;0.117647;0.039216;1.000000;;
   0.500000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  131;
  -0.490783;-0.073186;0.868203;,
  0.118674;-0.128437;0.984591;,
  0.085601;-0.996067;-0.022873;,
  -0.852877;-0.034478;-0.520972;,
  -0.296617;-0.142658;-0.944281;,
  0.054590;-0.159734;-0.985650;,
  -0.195426;-0.088828;0.976687;,
  0.199838;-0.150287;0.968235;,
  -0.862313;-0.029440;0.505520;,
  -0.660208;-0.091754;-0.745458;,
  -0.088057;-0.158067;-0.983494;,
  0.077575;-0.147853;-0.985962;,
  0.740935;-0.149419;0.654744;,
  0.735180;-0.158379;0.659110;,
  0.005354;-0.141310;-0.989951;,
  0.000379;-0.141630;-0.989920;,
  0.987058;-0.108452;0.118130;,
  0.991418;-0.123329;-0.043355;,
  -0.996043;0.030887;-0.083338;,
  -0.997154;0.017146;-0.073420;,
  0.972596;-0.129517;-0.193085;,
  0.073198;-0.996071;0.049854;,
  0.104749;-0.992342;0.065464;,
  -0.970662;-0.007456;0.240333;,
  0.957719;-0.154403;-0.242762;,
  0.083895;-0.996472;-0.002106;,
  0.134198;-0.976161;-0.170589;,
  0.094304;-0.994615;0.042981;,
  0.114410;-0.991788;0.057160;,
  0.078945;-0.996275;0.034701;,
  0.082527;-0.995896;0.037142;,
  0.103360;-0.992552;0.064471;,
  0.997154;-0.017146;0.073420;,
  0.996043;-0.030887;0.083338;,
  0.852877;0.034478;0.520972;,
  0.660208;0.091754;0.745458;,
  0.296617;0.142658;0.944281;,
  0.862313;0.029440;-0.505520;,
  0.195426;0.088828;-0.976687;,
  0.490783;0.073186;-0.868203;,
  0.088057;0.158067;0.983494;,
  -0.054590;0.159734;0.985650;,
  -0.199838;0.150287;-0.968235;,
  -0.118674;0.128437;-0.984591;,
  -0.740935;0.149419;-0.654744;,
  -0.005354;0.141310;0.989951;,
  -0.000379;0.141630;0.989920;,
  -0.077575;0.147853;0.985962;,
  -0.991418;0.123329;0.043355;,
  -0.987058;0.108452;-0.118130;,
  -0.972596;0.129517;0.193085;,
  -0.104749;0.992342;-0.065464;,
  -0.085601;0.996067;0.022873;,
  -0.073198;0.996071;-0.049854;,
  -0.735180;0.158379;-0.659110;,
  0.970662;0.007456;-0.240333;,
  -0.957719;0.154403;0.242762;,
  -0.134198;0.976161;0.170589;,
  -0.083895;0.996472;0.002106;,
  -0.114410;0.991788;-0.057160;,
  -0.094304;0.994615;-0.042981;,
  -0.082527;0.995896;-0.037142;,
  -0.078945;0.996275;-0.034701;,
  -0.103360;0.992552;-0.064471;,
  -0.881754;-0.154494;-0.445693;,
  0.000000;1.000000;0.000000;,
  -0.665382;-0.222785;0.712484;,
  -0.917874;-0.203329;-0.340830;,
  0.551398;-0.166120;-0.817535;,
  -0.472978;-0.204398;0.857038;,
  0.753723;-0.204398;0.624598;,
  -0.935618;-0.205351;0.287140;,
  0.975807;-0.205352;-0.075043;,
  -0.850059;-0.222212;0.477517;,
  0.965824;-0.222212;0.133437;,
  0.345484;-0.170913;-0.922729;,
  0.182675;-0.192865;0.964071;,
  -0.182152;-0.206614;-0.961318;,
  0.182404;-0.200136;0.962639;,
  0.970671;-0.235256;0.049522;,
  0.879907;-0.222785;0.419679;,
  -0.659097;-0.170913;-0.732379;,
  0.013611;-0.999851;0.010573;,
  -0.011733;-0.999736;0.019760;,
  0.003897;-0.999781;0.020566;,
  0.657583;-0.154496;-0.737371;,
  0.000000;-1.000000;-0.000000;,
  0.046868;-0.998898;0.002391;,
  -0.042744;-0.998898;0.019371;,
  0.822774;0.307607;-0.477935;,
  0.478122;0.823670;-0.304906;,
  0.297556;0.513035;-0.805143;,
  -0.074660;0.997209;0.000000;,
  0.478122;0.823670;0.304905;,
  0.999998;0.002169;0.000000;,
  0.838942;-0.291154;-0.459789;,
  0.822774;0.307606;0.477934;,
  0.838942;-0.291154;0.459789;,
  0.297555;0.513035;0.805143;,
  -0.568284;0.771382;-0.286397;,
  -0.568285;0.771381;0.286397;,
  -0.000000;-0.000001;-1.000000;,
  -0.365435;0.498260;-0.786253;,
  0.568282;-0.771384;-0.286396;,
  0.365434;-0.498260;-0.786254;,
  0.365435;-0.498260;0.786253;,
  0.568282;-0.771383;0.286397;,
  -0.365437;0.498260;0.786252;,
  -0.000000;-0.000001;1.000000;,
  -0.838942;0.291155;-0.459788;,
  -0.297554;-0.513035;-0.805144;,
  0.074662;-0.997209;0.000000;,
  -0.297553;-0.513035;0.805144;,
  -0.838942;0.291155;0.459787;,
  -0.822774;-0.307607;-0.477934;,
  -0.999998;-0.002170;0.000000;,
  -0.478119;-0.823671;-0.304906;,
  -0.478120;-0.823671;0.304905;,
  -0.822775;-0.307607;0.477933;,
  -0.853395;-0.521266;0.000000;,
  -0.875093;0.483955;0.000000;,
  -0.560505;-0.001793;0.828149;,
  0.064980;-0.855504;0.513703;,
  0.064979;-0.855504;-0.513703;,
  -0.560504;-0.001795;-0.828150;,
  -0.064980;0.855504;0.513703;,
  0.560505;0.001794;0.828149;,
  0.875092;-0.483956;0.000000;,
  0.560504;0.001796;-0.828150;,
  -0.064979;0.855504;-0.513703;,
  0.853394;0.521267;0.000000;;
  166;
  3;3,18,19;,
  3;4,3,9;,
  3;0,6,8;,
  3;5,4,10;,
  3;1,7,6;,
  3;7,1,12;,
  3;11,15,14;,
  3;20,16,17;,
  3;21,2,22;,
  3;16,13,12;,
  3;23,8,19;,
  3;3,19,9;,
  3;4,9,10;,
  3;0,8,23;,
  3;5,10,11;,
  3;1,6,0;,
  3;7,12,13;,
  3;11,14,5;,
  3;20,17,24;,
  3;2,25,26;,
  3;25,27,28;,
  3;27,29,30;,
  3;29,25,21;,
  3;31,21,22;,
  3;2,21,25;,
  3;27,25,29;,
  3;16,12,17;,
  3;23,19,18;,
  3;32,33,34;,
  3;35,34,36;,
  3;37,38,39;,
  3;40,36,41;,
  3;38,42,43;,
  3;44,43,42;,
  3;45,46,47;,
  3;48,49,50;,
  3;51,52,53;,
  3;44,54,49;,
  3;32,37,55;,
  3;35,32,34;,
  3;40,35,36;,
  3;55,37,39;,
  3;47,40,41;,
  3;39,38,43;,
  3;54,44,42;,
  3;41,45,47;,
  3;56,48,50;,
  3;57,58,52;,
  3;59,60,58;,
  3;61,62,60;,
  3;53,58,62;,
  3;51,53,63;,
  3;58,53,52;,
  3;62,58,60;,
  3;48,44,49;,
  3;33,32,55;,
  3;65,65,65;,
  3;78,76,70;,
  3;68,77,75;,
  3;71,64,67;,
  3;72,74,79;,
  3;80,70,74;,
  3;66,71,73;,
  3;65,65,65;,
  3;65,65,65;,
  3;67,64,81;,
  3;78,66,69;,
  3;65,65,65;,
  3;82,83,84;,
  3;65,65,65;,
  3;78,70,80;,
  3;68,75,85;,
  3;71,67,73;,
  3;72,68,85;,
  3;80,74,72;,
  3;66,73,69;,
  3;65,65,65;,
  3;65,65,65;,
  3;67,81,77;,
  3;78,69,76;,
  3;65,65,65;,
  3;83,82,86;,
  3;86,86,86;,
  3;82,84,87;,
  3;84,83,88;,
  3;86,82,86;,
  3;113,118,121;,
  3;115,118,113;,
  3;115,119,118;,
  3;112,117,122;,
  3;118,117,112;,
  3;118,119,117;,
  3;111,116,123;,
  3;117,116,111;,
  3;117,119,116;,
  3;110,114,124;,
  3;116,114,110;,
  3;116,119,114;,
  3;109,115,120;,
  3;114,115,109;,
  3;114,119,115;,
  3;107,113,121;,
  3;100,113,107;,
  3;100,120,113;,
  3;105,112,122;,
  3;108,112,105;,
  3;108,121,112;,
  3;103,111,123;,
  3;106,111,103;,
  3;106,122,111;,
  3;101,110,124;,
  3;104,110,101;,
  3;104,123,110;,
  3;99,109,120;,
  3;102,109,99;,
  3;102,124,109;,
  3;98,108,126;,
  3;107,108,98;,
  3;107,121,108;,
  3;97,106,127;,
  3;105,106,97;,
  3;105,122,106;,
  3;95,104,128;,
  3;103,104,95;,
  3;103,123,104;,
  3;91,102,129;,
  3;101,102,91;,
  3;101,124,102;,
  3;92,100,125;,
  3;99,100,92;,
  3;99,120,100;,
  3;96,98,126;,
  3;93,98,96;,
  3;93,125,98;,
  3;94,97,127;,
  3;96,97,94;,
  3;96,126,97;,
  3;89,95,128;,
  3;94,95,89;,
  3;94,127,95;,
  3;90,93,130;,
  3;92,93,90;,
  3;92,125,93;,
  3;90,91,129;,
  3;89,91,90;,
  3;89,128,91;,
  3;120,115,113;,
  3;121,118,112;,
  3;122,117,111;,
  3;123,116,110;,
  3;124,114,109;,
  3;125,100,107;,
  3;126,108,105;,
  3;127,106,103;,
  3;128,104,101;,
  3;129,102,99;,
  3;125,107,98;,
  3;126,105,97;,
  3;127,103,95;,
  3;128,101,91;,
  3;129,99,92;,
  3;130,93,96;,
  3;130,96,94;,
  3;130,94,89;,
  3;129,92,90;,
  3;130,89,90;;
 }
 MeshTextureCoords {
  79;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
