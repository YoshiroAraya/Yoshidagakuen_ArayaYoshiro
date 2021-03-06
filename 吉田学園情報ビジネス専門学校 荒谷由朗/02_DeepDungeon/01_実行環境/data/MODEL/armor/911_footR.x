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
 26;
 -2.58408;-2.06938;0.01373;,
 -2.58408;-4.75325;0.01373;,
 -1.50313;-4.75325;2.59355;,
 -1.50313;-2.06938;2.59355;,
 0.18138;0.22530;-4.91704;,
 -0.26246;-2.06938;-11.90112;,
 -2.34634;-2.06938;-10.67464;,
 -3.39272;-2.06938;-2.58339;,
 0.71924;-2.06938;3.54636;,
 0.71924;-4.75325;3.54636;,
 2.80312;-4.75325;2.31987;,
 2.80312;-2.06938;2.31987;,
 3.54879;-4.75325;-0.37602;,
 3.54879;-2.06938;-0.37602;,
 -2.22219;-4.75325;-2.65777;,
 2.85162;-4.75325;-2.98024;,
 4.02215;-2.06938;-3.05462;,
 -0.26246;-4.75325;-11.90112;,
 -2.34634;-4.75325;-10.67464;,
 1.95989;-2.06938;-10.94830;,
 1.95991;-4.75325;-10.94830;,
 0.71924;0.00717;3.54636;,
 -1.50313;0.00717;2.59355;,
 2.80312;0.00717;2.31987;,
 3.54879;0.00717;-0.37602;,
 -2.58408;0.00717;0.01373;;
 
 31;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;7,14,1,0;,
 4;13,12,15,16;,
 4;3,2,9,8;,
 4;5,17,18,6;,
 4;19,20,17,5;,
 4;7,6,18,14;,
 4;15,20,19,16;,
 4;16,19,5,4;,
 4;8,21,22,3;,
 4;11,23,21,8;,
 4;13,24,23,11;,
 4;3,22,25,0;,
 3;0,25,7;,
 3;13,16,24;,
 3;7,25,4;,
 3;4,24,16;,
 3;25,24,4;,
 4;25,22,23,24;,
 3;21,23,22;,
 3;15,14,18;,
 3;1,12,2;,
 3;9,2,10;,
 3;15,18,20;,
 3;10,2,12;,
 3;14,15,1;,
 3;17,20,18;,
 3;12,1,15;;
 
 MeshMaterialList {
  1;
  31;
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
   0.377600;0.377600;0.377600;1.000000;;
   0.500000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  29;
  -0.529324;0.804624;-0.269065;,
  0.988397;0.075775;-0.131643;,
  -0.710018;0.000000;0.704184;,
  0.793450;0.000000;0.608635;,
  -0.955828;-0.051664;0.289349;,
  0.984768;-0.051664;0.166021;,
  0.063425;0.000000;0.997987;,
  -0.016772;0.964399;-0.263918;,
  -0.014693;0.972794;-0.231205;,
  0.063425;0.000000;0.997987;,
  -0.966708;-0.103914;0.233833;,
  0.988532;-0.103914;0.109575;,
  0.972479;-0.203305;-0.113808;,
  -0.979062;-0.203307;0.010215;,
  -0.384634;0.903080;-0.191058;,
  -0.845968;-0.114903;-0.520706;,
  0.773247;-0.114900;-0.623608;,
  -0.063420;0.000001;-0.997987;,
  -0.939608;0.000000;0.342253;,
  0.975375;0.000000;0.220553;,
  0.063425;0.000000;0.997987;,
  -0.984667;-0.137361;0.107526;,
  0.357354;0.903080;-0.238213;,
  -0.235330;0.966203;-0.105218;,
  0.220117;0.966203;-0.134162;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;;
  31;
  4;4,10,2,2;,
  4;7,8,14,0;,
  4;6,9,3,3;,
  4;3,3,11,5;,
  4;21,13,10,4;,
  4;5,11,12,1;,
  4;2,2,9,6;,
  4;17,17,15,15;,
  4;16,16,17,17;,
  4;21,15,15,13;,
  4;12,16,16,1;,
  4;22,22,8,7;,
  4;6,20,2,2;,
  4;3,3,20,6;,
  4;5,19,3,3;,
  4;2,2,18,4;,
  3;4,18,21;,
  3;5,1,19;,
  3;0,23,7;,
  3;7,24,1;,
  3;23,24,7;,
  4;23,25,25,24;,
  3;26,25,25;,
  3;27,27,27;,
  3;27,27,27;,
  3;28,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;;
 }
 MeshTextureCoords {
  26;
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
