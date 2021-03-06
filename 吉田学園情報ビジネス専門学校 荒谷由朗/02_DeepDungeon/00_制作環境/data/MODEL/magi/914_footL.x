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
 31;
 -2.08507;-0.91203;-0.94033;,
 -2.08507;-3.09264;-0.94033;,
 -1.21699;-3.09264;0.92440;,
 -1.21699;-0.91203;0.92440;,
 -0.85830;1.30127;-9.58502;,
 -1.13065;-0.58331;-12.21138;,
 -3.14290;-0.58331;-10.79881;,
 -4.50295;-0.22456;-7.00995;,
 0.44327;-0.91203;1.56094;,
 0.44327;-3.09264;1.56094;,
 1.93939;-3.09264;0.60013;,
 1.93939;-0.91203;0.60013;,
 2.41020;-3.09264;-1.40216;,
 2.41020;-0.91203;-1.40216;,
 -3.46465;-1.08526;-2.48928;,
 -1.89557;-3.09264;-2.91370;,
 1.82342;-3.09264;-3.29577;,
 3.44603;-1.08526;-3.19924;,
 -1.13065;-3.54578;-12.21138;,
 -3.14290;-3.54578;-10.79881;,
 1.14520;-0.58331;-11.23933;,
 1.14520;-3.54578;-11.23933;,
 -3.80079;-4.29105;-7.08207;,
 2.54582;-4.29105;-7.73411;,
 3.24798;-0.22456;-7.80624;,
 0.51951;0.76523;2.30300;,
 -1.69800;0.76523;1.45280;,
 2.51779;0.76523;1.01969;,
 3.14661;0.76523;-1.65461;,
 -2.85743;0.76523;-1.03780;,
 -0.38525;1.34840;-6.50355;;
 
 37;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;14,15,1,0;,
 4;13,12,16,17;,
 4;3,2,9,8;,
 4;5,18,19,6;,
 4;20,21,18,5;,
 4;7,6,19,22;,
 4;23,21,20,24;,
 4;24,20,5,4;,
 4;8,25,26,3;,
 4;11,27,25,8;,
 4;13,28,27,11;,
 4;3,26,29,0;,
 3;0,29,14;,
 3;13,17,28;,
 3;14,29,30;,
 3;30,28,17;,
 3;29,28,30;,
 4;29,26,27,28;,
 3;25,27,26;,
 3;21,19,18;,
 3;12,1,16;,
 4;17,24,4,30;,
 4;16,23,24,17;,
 4;14,7,22,15;,
 4;30,4,7,14;,
 3;19,21,22;,
 3;23,22,21;,
 3;1,9,2;,
 3;9,12,10;,
 3;16,15,23;,
 3;9,1,12;,
 3;15,16,1;,
 3;23,15,22;;
 
 MeshMaterialList {
  1;
  37;
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
   0.380392;0.160784;0.058824;1.000000;;
   0.500000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  -0.820288;-0.350134;0.452254;,
  0.906337;-0.353909;0.230870;,
  -0.668245;-0.201086;0.716249;,
  0.799919;-0.201087;0.565415;,
  -0.850135;-0.253949;0.461281;,
  0.926166;-0.253950;0.278795;,
  0.099932;-0.209493;0.972690;,
  -0.633380;0.768969;-0.086696;,
  -0.575775;0.449908;-0.682690;,
  0.102200;0.000000;0.994764;,
  -0.682085;0.000000;0.731273;,
  -0.906281;-0.174774;0.384850;,
  0.965599;-0.174775;0.192545;,
  0.921664;-0.377628;0.089071;,
  -0.862091;-0.375244;0.340574;,
  0.816524;0.000000;0.577311;,
  -0.768459;0.278400;-0.576163;,
  -0.814083;-0.043540;-0.579115;,
  0.633682;0.278955;-0.721548;,
  -0.104012;0.000000;-0.994576;,
  0.677921;-0.043564;-0.733843;,
  -0.627702;-0.391908;0.672605;,
  0.751349;-0.391909;0.530926;,
  -0.781311;-0.328961;0.530413;,
  0.872834;-0.328962;0.360478;,
  0.093381;-0.406370;0.908924;,
  -0.964589;-0.260849;0.039066;,
  -0.426611;0.895231;-0.128701;,
  -0.014919;0.980356;-0.196669;,
  0.939311;-0.257145;-0.227092;,
  0.422157;0.450578;-0.786615;,
  0.397500;0.888591;-0.228909;,
  -0.463360;0.868022;-0.178425;,
  0.607290;0.760497;-0.229877;,
  0.417403;0.868022;-0.268909;,
  0.011423;0.993733;0.111193;,
  0.000000;1.000000;0.000000;,
  -0.013765;-0.990888;-0.133982;,
  -0.010329;-0.994879;-0.100544;,
  0.000000;-1.000000;0.000000;,
  0.009138;-0.995994;0.088951;,
  -0.004754;-0.998917;-0.046274;,
  0.011563;-0.993579;0.112551;,
  0.018277;-0.983878;0.177902;;
  37;
  4;4,11,10,2;,
  4;28,8,16,27;,
  4;6,9,15,3;,
  4;3,15,12,5;,
  4;0,14,11,4;,
  4;5,12,13,1;,
  4;2,10,9,6;,
  4;8,19,17,16;,
  4;18,20,19,30;,
  4;26,16,17,26;,
  4;29,20,18,29;,
  4;31,18,30,28;,
  4;6,25,21,2;,
  4;3,22,25,6;,
  4;5,24,22,3;,
  4;2,21,23,4;,
  3;4,23,0;,
  3;5,1,24;,
  3;7,32,7;,
  3;33,34,33;,
  3;35,35,35;,
  4;32,36,36,34;,
  3;36,36,36;,
  3;37,38,39;,
  3;39,39,40;,
  4;33,31,28,33;,
  4;13,29,29,1;,
  4;0,26,26,14;,
  4;7,28,27,7;,
  3;38,37,41;,
  3;42,41,37;,
  3;39,39,39;,
  3;39,39,39;,
  3;40,43,42;,
  3;39,39,39;,
  3;43,40,39;,
  3;42,43,41;;
 }
 MeshTextureCoords {
  31;
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
