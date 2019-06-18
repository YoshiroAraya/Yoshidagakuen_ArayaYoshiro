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
 301;
 0.00262;0.00000;-6.94683;,
 -1.35900;0.00000;-6.81272;,
 -1.33284;1.36162;-6.68119;,
 0.00262;1.36162;-6.81272;,
 0.00262;2.67092;-6.41555;,
 -1.25536;2.67092;-6.29165;,
 -1.12953;3.87758;-5.65908;,
 0.00262;3.87758;-5.77058;,
 0.00262;4.93522;-4.90260;,
 -0.96019;4.93522;-4.80777;,
 -0.75386;5.80320;-3.77045;,
 0.00262;5.80320;-3.84496;,
 0.00262;-6.84534;-1.32900;,
 -0.26302;-6.84534;-1.30284;,
 -0.51845;-6.44817;-2.58698;,
 0.00262;-6.44817;-2.63830;,
 0.00262;6.44817;-2.63830;,
 -0.51845;6.44817;-2.58698;,
 -0.26302;6.84534;-1.30284;,
 0.00262;6.84534;-1.32900;,
 0.00262;-5.80320;-3.84496;,
 -0.75386;-5.80320;-3.77045;,
 -0.96019;-4.93522;-4.80777;,
 0.00262;-4.93522;-4.90260;,
 0.00262;-3.87758;-5.77058;,
 -1.12953;-3.87758;-5.65908;,
 -1.25536;-2.67092;-6.29165;,
 0.00262;-2.67092;-6.41555;,
 0.00262;-1.36162;-6.81272;,
 -1.33284;-1.36162;-6.68119;,
 -1.48126;5.80320;-3.54979;,
 -1.01950;6.44817;-2.43499;,
 -1.01950;-6.44817;-2.43499;,
 -1.48126;-5.80320;-3.54979;,
 -1.88601;-4.93522;-4.52693;,
 -2.21817;-3.87758;-5.32884;,
 -2.46499;-2.67092;-5.92472;,
 -2.61698;-1.36162;-6.29165;,
 -2.66830;0.00000;-6.41555;,
 -2.61698;1.36162;-6.29165;,
 -2.46499;2.67092;-5.92471;,
 -2.21817;3.87758;-5.32884;,
 -1.88601;4.93522;-4.52693;,
 -0.51845;-6.84534;-1.22535;,
 -0.51845;6.84534;-1.22536;,
 -2.15165;5.80320;-3.19147;,
 -1.48126;6.44817;-2.18817;,
 -1.48126;-6.44817;-2.18817;,
 -2.15165;-5.80320;-3.19147;,
 -2.73924;-4.93522;-4.07086;,
 -3.22147;-3.87758;-4.79257;,
 -3.57979;-2.67092;-5.32884;,
 -3.80045;-1.36162;-5.65908;,
 -3.87496;0.00000;-5.77058;,
 -3.80045;1.36162;-5.65908;,
 -3.57979;2.67092;-5.32884;,
 -3.22147;3.87758;-4.79257;,
 -2.73924;4.93522;-4.07086;,
 -0.75386;-6.84534;-1.09953;,
 -0.75386;6.84534;-1.09953;,
 -2.73924;5.80320;-2.70924;,
 -1.88601;6.44817;-1.85601;,
 -1.88601;-6.44817;-1.85601;,
 -2.73924;-5.80320;-2.70924;,
 -3.48711;-4.93522;-3.45711;,
 -4.10087;-3.87758;-4.07086;,
 -4.55693;-2.67092;-4.52693;,
 -4.83777;-1.36162;-4.80777;,
 -4.93260;0.00000;-4.90260;,
 -4.83777;1.36162;-4.80777;,
 -4.55693;2.67092;-4.52693;,
 -4.10087;3.87758;-4.07086;,
 -3.48711;4.93522;-3.45711;,
 -0.96019;-6.84534;-0.93019;,
 -0.96019;6.84534;-0.93019;,
 -3.22147;5.80320;-2.12164;,
 -2.21817;6.44817;-1.45126;,
 -2.21817;-6.44817;-1.45126;,
 -3.22147;-5.80320;-2.12164;,
 -4.10087;-4.93522;-2.70924;,
 -4.82257;-3.87758;-3.19147;,
 -5.35884;-2.67092;-3.54979;,
 -5.68908;-1.36162;-3.77045;,
 -5.80058;0.00000;-3.84495;,
 -5.68908;1.36162;-3.77045;,
 -5.35884;2.67092;-3.54979;,
 -4.82257;3.87758;-3.19147;,
 -4.10087;4.93522;-2.70924;,
 -1.12953;-6.84534;-0.72386;,
 -1.12953;6.84534;-0.72386;,
 -3.57979;5.80320;-1.45126;,
 -2.46499;6.44817;-0.98950;,
 -2.46499;-6.44817;-0.98950;,
 -3.57979;-5.80320;-1.45126;,
 -4.55693;-4.93522;-1.85600;,
 -5.35884;-3.87758;-2.18817;,
 -5.95472;-2.67092;-2.43499;,
 -6.32165;-1.36162;-2.58698;,
 -6.44556;0.00000;-2.63830;,
 -6.32165;1.36162;-2.58698;,
 -5.95472;2.67092;-2.43499;,
 -5.35884;3.87758;-2.18817;,
 -4.55693;4.93522;-1.85600;,
 -1.25536;-6.84534;-0.48845;,
 -1.25536;6.84534;-0.48845;,
 -3.80045;5.80320;-0.72386;,
 -2.61698;6.44817;-0.48845;,
 -2.61698;-6.44817;-0.48845;,
 -3.80045;-5.80320;-0.72386;,
 -4.83777;-4.93522;-0.93019;,
 -5.68908;-3.87758;-1.09953;,
 -6.32165;-2.67092;-1.22536;,
 -6.71119;-1.36162;-1.30284;,
 -6.84273;0.00000;-1.32900;,
 -6.71119;1.36162;-1.30284;,
 -6.32165;2.67092;-1.22536;,
 -5.68908;3.87758;-1.09953;,
 -4.83777;4.93522;-0.93019;,
 -1.33284;-6.84534;-0.23302;,
 -1.33284;6.84534;-0.23302;,
 -3.87496;5.80320;0.03262;,
 -2.66830;6.44817;0.03262;,
 -2.66830;-6.44817;0.03262;,
 -3.87496;-5.80320;0.03262;,
 -4.93260;-4.93522;0.03262;,
 -5.80058;-3.87758;0.03262;,
 -6.44555;-2.67092;0.03262;,
 -6.84272;-1.36162;0.03262;,
 -6.97683;0.00000;0.03262;,
 -6.84272;1.36162;0.03262;,
 -6.44555;2.67092;0.03262;,
 -5.80058;3.87758;0.03262;,
 -4.93260;4.93522;0.03262;,
 -1.35900;-6.84534;0.03262;,
 -1.35901;6.84534;0.03262;,
 3.88020;5.80320;0.03262;,
 3.80569;5.80320;-0.72386;,
 2.62222;6.44817;-0.48845;,
 2.67354;6.44817;0.03262;,
 2.67354;-6.44817;0.03262;,
 2.62222;-6.44817;-0.48845;,
 3.80569;-5.80320;-0.72386;,
 3.88019;-5.80320;0.03262;,
 4.93784;-4.93522;0.03262;,
 4.84301;-4.93522;-0.93019;,
 5.69431;-3.87758;-1.09953;,
 5.80582;-3.87758;0.03262;,
 6.45079;-2.67092;0.03262;,
 6.32689;-2.67092;-1.22535;,
 6.71643;-1.36162;-1.30284;,
 6.84796;-1.36162;0.03262;,
 6.98207;0.00000;0.03262;,
 6.84796;0.00000;-1.32900;,
 6.71643;1.36162;-1.30284;,
 6.84796;1.36162;0.03262;,
 6.45079;2.67092;0.03262;,
 6.32689;2.67092;-1.22535;,
 5.69431;3.87758;-1.09953;,
 5.80582;3.87758;0.03262;,
 4.93784;4.93522;0.03262;,
 4.84301;4.93522;-0.93019;,
 1.36424;-6.84534;0.03262;,
 1.33808;-6.84534;-0.23302;,
 1.33808;6.84534;-0.23302;,
 1.36424;6.84534;0.03262;,
 3.58503;5.80320;-1.45126;,
 2.47023;6.44817;-0.98949;,
 2.47023;-6.44817;-0.98949;,
 3.58503;-5.80320;-1.45126;,
 4.56217;-4.93522;-1.85600;,
 5.36408;-3.87758;-2.18817;,
 5.95995;-2.67092;-2.43499;,
 6.32689;-1.36162;-2.58698;,
 6.45079;0.00000;-2.63830;,
 6.32689;1.36162;-2.58698;,
 5.95995;2.67092;-2.43499;,
 5.36408;3.87758;-2.18817;,
 4.56217;4.93522;-1.85600;,
 1.26060;-6.84534;-0.48845;,
 1.26060;6.84534;-0.48845;,
 3.22671;5.80320;-2.12164;,
 2.22341;6.44817;-1.45126;,
 2.22341;-6.44817;-1.45126;,
 3.22670;-5.80320;-2.12164;,
 4.10610;-4.93522;-2.70924;,
 4.82780;-3.87758;-3.19146;,
 5.36408;-2.67092;-3.54979;,
 5.69431;-1.36162;-3.77045;,
 5.80582;0.00000;-3.84495;,
 5.69431;1.36162;-3.77045;,
 5.36408;2.67092;-3.54979;,
 4.82780;3.87758;-3.19146;,
 4.10610;4.93522;-2.70924;,
 1.13477;-6.84534;-0.72385;,
 1.13477;6.84534;-0.72386;,
 2.74448;5.80320;-2.70924;,
 1.89125;6.44817;-1.85600;,
 1.89124;-6.44817;-1.85600;,
 2.74448;-5.80320;-2.70924;,
 3.49235;-4.93522;-3.45710;,
 4.10610;-3.87758;-4.07086;,
 4.56217;-2.67092;-4.52692;,
 4.84301;-1.36162;-4.80777;,
 4.93784;0.00000;-4.90260;,
 4.84301;1.36162;-4.80777;,
 4.56217;2.67092;-4.52692;,
 4.10610;3.87758;-4.07086;,
 3.49235;4.93522;-3.45710;,
 0.96543;-6.84534;-0.93019;,
 0.96543;6.84534;-0.93019;,
 2.15689;5.80320;-3.19146;,
 1.48650;6.44817;-2.18817;,
 1.48650;-6.44817;-2.18817;,
 2.15688;-5.80320;-3.19146;,
 2.74448;-4.93522;-4.07086;,
 3.22670;-3.87758;-4.79256;,
 3.58503;-2.67092;-5.32884;,
 3.80569;-1.36162;-5.65907;,
 3.88019;0.00000;-5.77058;,
 3.80569;1.36162;-5.65907;,
 3.58503;2.67092;-5.32884;,
 3.22670;3.87758;-4.79256;,
 2.74448;4.93522;-4.07086;,
 0.75910;-6.84534;-1.09953;,
 0.75910;6.84534;-1.09953;,
 1.48650;5.80320;-3.54979;,
 1.02474;6.44817;-2.43499;,
 1.02474;-6.44817;-2.43499;,
 1.48650;-5.80320;-3.54979;,
 1.89125;-4.93522;-4.52692;,
 2.22341;-3.87758;-5.32884;,
 2.47023;-2.67092;-5.92471;,
 2.62222;-1.36162;-6.29165;,
 2.67354;0.00000;-6.41555;,
 2.62222;1.36162;-6.29165;,
 2.47023;2.67092;-5.92471;,
 2.22341;3.87758;-5.32884;,
 1.89125;4.93522;-4.52692;,
 0.52369;-6.84534;-1.22535;,
 0.52369;6.84534;-1.22535;,
 0.75910;5.80320;-3.77045;,
 0.52369;6.44817;-2.58698;,
 0.52369;-6.44817;-2.58698;,
 0.75910;-5.80320;-3.77045;,
 0.96543;-4.93522;-4.80777;,
 1.13477;-3.87758;-5.65907;,
 1.26060;-2.67092;-6.29165;,
 1.33808;-1.36162;-6.68119;,
 1.36424;0.00000;-6.81272;,
 1.33808;1.36162;-6.68119;,
 1.26060;2.67092;-6.29165;,
 1.13477;3.87758;-5.65907;,
 0.96543;4.93522;-4.80777;,
 0.26826;-6.84534;-1.30284;,
 0.26826;6.84534;-1.30284;,
 0.00262;-6.97945;0.03262;,
 0.00262;6.97945;0.03262;,
 0.00262;-6.97945;0.03262;,
 0.00262;-6.44817;-2.63830;,
 0.00262;-5.80320;-3.84496;,
 0.00262;-4.93522;-4.90260;,
 0.00262;-3.87758;-5.77058;,
 0.00262;-2.67092;-6.41555;,
 0.00262;-1.36162;-6.81272;,
 0.00262;-6.84534;-1.32900;,
 0.00262;-5.46443;39.50682;,
 0.00262;-8.04765;-0.00786;,
 6.16905;-6.63772;-0.00787;,
 3.84699;-4.38212;39.50682;,
 0.00262;5.52547;39.50682;,
 3.84700;4.44317;39.50682;,
 6.16905;6.69877;-0.00787;,
 0.00262;8.10870;-0.00787;,
 0.00262;0.03052;39.50682;,
 6.22795;0.03052;39.50682;,
 3.84700;4.44317;39.50682;,
 0.00262;5.52547;39.50682;,
 6.22795;0.03052;39.50682;,
 9.49929;0.03052;-0.00787;,
 9.49929;0.03052;-0.00787;,
 0.00262;0.03052;-0.00786;,
 0.00262;8.10870;-0.00787;,
 6.16905;6.69877;-0.00787;,
 -3.84176;4.44317;39.50684;,
 -6.16381;6.69877;-0.00786;,
 -9.49405;0.03052;-0.00786;,
 -6.22271;0.03052;39.50682;,
 6.16905;-6.63772;-0.00787;,
 0.00262;-8.04765;-0.00786;,
 -6.16381;-6.63772;-0.00785;,
 -3.84176;-4.38212;39.50682;,
 0.00262;-5.46443;39.50682;,
 3.84699;-4.38212;39.50682;,
 -9.49405;0.03052;-0.00786;,
 -6.16381;6.69877;-0.00786;,
 -3.84176;-4.38212;39.50682;,
 -6.22271;0.03052;39.50682;,
 -3.84176;4.44317;39.50684;,
 -6.16381;-6.63772;-0.00785;,
 0.00262;-8.04765;-0.00786;,
 0.00262;-5.46443;39.50682;;
 
 272;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,1,0;,
 4;3,2,5,4;,
 4;7,6,9,8;,
 4;11,10,17,16;,
 4;15,14,21,20;,
 4;23,22,25,24;,
 4;27,26,29,28;,
 4;10,30,31,17;,
 4;14,32,33,21;,
 4;22,34,35,25;,
 4;26,36,37,29;,
 4;1,38,39,2;,
 4;5,40,41,6;,
 4;9,42,30,10;,
 4;13,43,32,14;,
 4;17,31,44,18;,
 4;21,33,34,22;,
 4;25,35,36,26;,
 4;29,37,38,1;,
 4;2,39,40,5;,
 4;6,41,42,9;,
 4;30,45,46,31;,
 4;32,47,48,33;,
 4;34,49,50,35;,
 4;36,51,52,37;,
 4;38,53,54,39;,
 4;40,55,56,41;,
 4;42,57,45,30;,
 4;43,58,47,32;,
 4;31,46,59,44;,
 4;33,48,49,34;,
 4;35,50,51,36;,
 4;37,52,53,38;,
 4;39,54,55,40;,
 4;41,56,57,42;,
 4;45,60,61,46;,
 4;47,62,63,48;,
 4;49,64,65,50;,
 4;51,66,67,52;,
 4;53,68,69,54;,
 4;55,70,71,56;,
 4;57,72,60,45;,
 4;58,73,62,47;,
 4;46,61,74,59;,
 4;48,63,64,49;,
 4;50,65,66,51;,
 4;52,67,68,53;,
 4;54,69,70,55;,
 4;56,71,72,57;,
 4;60,75,76,61;,
 4;62,77,78,63;,
 4;64,79,80,65;,
 4;66,81,82,67;,
 4;68,83,84,69;,
 4;70,85,86,71;,
 4;72,87,75,60;,
 4;73,88,77,62;,
 4;61,76,89,74;,
 4;63,78,79,64;,
 4;65,80,81,66;,
 4;67,82,83,68;,
 4;69,84,85,70;,
 4;71,86,87,72;,
 4;75,90,91,76;,
 4;77,92,93,78;,
 4;79,94,95,80;,
 4;81,96,97,82;,
 4;83,98,99,84;,
 4;85,100,101,86;,
 4;87,102,90,75;,
 4;88,103,92,77;,
 4;76,91,104,89;,
 4;78,93,94,79;,
 4;80,95,96,81;,
 4;82,97,98,83;,
 4;84,99,100,85;,
 4;86,101,102,87;,
 4;90,105,106,91;,
 4;92,107,108,93;,
 4;94,109,110,95;,
 4;96,111,112,97;,
 4;98,113,114,99;,
 4;100,115,116,101;,
 4;102,117,105,90;,
 4;103,118,107,92;,
 4;91,106,119,104;,
 4;93,108,109,94;,
 4;95,110,111,96;,
 4;97,112,113,98;,
 4;99,114,115,100;,
 4;101,116,117,102;,
 4;105,120,121,106;,
 4;107,122,123,108;,
 4;109,124,125,110;,
 4;111,126,127,112;,
 4;113,128,129,114;,
 4;115,130,131,116;,
 4;117,132,120,105;,
 4;118,133,122,107;,
 4;106,121,134,119;,
 4;108,123,124,109;,
 4;110,125,126,111;,
 4;112,127,128,113;,
 4;114,129,130,115;,
 4;116,131,132,117;,
 4;135,136,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;159,160,136,135;,
 4;161,162,140,139;,
 4;138,137,163,164;,
 4;142,141,144,143;,
 4;146,145,148,147;,
 4;150,149,152,151;,
 4;154,153,156,155;,
 4;158,157,160,159;,
 4;136,165,166,137;,
 4;140,167,168,141;,
 4;144,169,170,145;,
 4;148,171,172,149;,
 4;152,173,174,153;,
 4;156,175,176,157;,
 4;160,177,165,136;,
 4;162,178,167,140;,
 4;137,166,179,163;,
 4;141,168,169,144;,
 4;145,170,171,148;,
 4;149,172,173,152;,
 4;153,174,175,156;,
 4;157,176,177,160;,
 4;165,180,181,166;,
 4;167,182,183,168;,
 4;169,184,185,170;,
 4;171,186,187,172;,
 4;173,188,189,174;,
 4;175,190,191,176;,
 4;177,192,180,165;,
 4;178,193,182,167;,
 4;166,181,194,179;,
 4;168,183,184,169;,
 4;170,185,186,171;,
 4;172,187,188,173;,
 4;174,189,190,175;,
 4;176,191,192,177;,
 4;180,195,196,181;,
 4;182,197,198,183;,
 4;184,199,200,185;,
 4;186,201,202,187;,
 4;188,203,204,189;,
 4;190,205,206,191;,
 4;192,207,195,180;,
 4;193,208,197,182;,
 4;181,196,209,194;,
 4;183,198,199,184;,
 4;185,200,201,186;,
 4;187,202,203,188;,
 4;189,204,205,190;,
 4;191,206,207,192;,
 4;195,210,211,196;,
 4;197,212,213,198;,
 4;199,214,215,200;,
 4;201,216,217,202;,
 4;203,218,219,204;,
 4;205,220,221,206;,
 4;207,222,210,195;,
 4;208,223,212,197;,
 4;196,211,224,209;,
 4;198,213,214,199;,
 4;200,215,216,201;,
 4;202,217,218,203;,
 4;204,219,220,205;,
 4;206,221,222,207;,
 4;210,225,226,211;,
 4;212,227,228,213;,
 4;214,229,230,215;,
 4;216,231,232,217;,
 4;218,233,234,219;,
 4;220,235,236,221;,
 4;222,237,225,210;,
 4;223,238,227,212;,
 4;211,226,239,224;,
 4;213,228,229,214;,
 4;215,230,231,216;,
 4;217,232,233,218;,
 4;219,234,235,220;,
 4;221,236,237,222;,
 4;225,240,241,226;,
 4;227,242,243,228;,
 4;229,244,245,230;,
 4;231,246,247,232;,
 4;233,248,249,234;,
 4;235,250,251,236;,
 4;237,252,240,225;,
 4;238,253,242,227;,
 4;226,241,254,239;,
 4;228,243,244,229;,
 4;230,245,246,231;,
 4;232,247,248,233;,
 4;234,249,250,235;,
 4;236,251,252,237;,
 3;255,13,12;,
 3;19,18,256;,
 3;18,44,256;,
 3;255,43,13;,
 3;44,59,256;,
 3;255,58,43;,
 3;59,74,256;,
 3;255,73,58;,
 3;74,89,256;,
 3;255,88,73;,
 3;89,104,256;,
 3;255,103,88;,
 3;104,119,256;,
 3;255,118,103;,
 3;119,134,256;,
 3;255,133,118;,
 3;164,163,256;,
 3;257,162,161;,
 3;163,179,256;,
 3;257,178,162;,
 3;179,194,256;,
 3;257,193,178;,
 3;194,209,256;,
 3;257,208,193;,
 3;209,224,256;,
 3;257,223,208;,
 3;224,239,256;,
 3;257,238,223;,
 3;239,254,256;,
 3;257,253,238;,
 4;240,11,16,241;,
 4;242,258,259,243;,
 3;254,19,256;,
 4;244,260,261,245;,
 4;246,262,263,247;,
 4;248,0,3,249;,
 4;250,4,7,251;,
 4;252,8,11,240;,
 4;253,264,258,242;,
 4;241,16,19,254;,
 4;243,259,260,244;,
 4;245,261,262,246;,
 4;247,263,0,248;,
 4;249,3,4,250;,
 4;251,7,8,252;,
 3;257,264,253;,
 4;265,266,267,268;,
 4;269,270,271,272;,
 4;273,274,275,276;,
 4;277,278,271,270;,
 4;279,280,281,282;,
 4;283,284,285,286;,
 4;287,288,280,279;,
 4;286,285,289,290;,
 4;291,292,274,273;,
 4;268,267,278,277;,
 4;280,293,294,281;,
 4;283,269,272,284;,
 4;295,291,273,296;,
 4;296,273,276,297;,
 4;288,298,293,280;,
 4;290,289,299,300;;
 
 MeshMaterialList {
  1;
  272;
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
   0.280000;0.280000;0.280000;1.000000;;
   40.000000;
   0.500000;0.500000;0.500000;;
   0.296000;0.296000;0.296000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\player\\L\\L_arm1_UV.jpg";
   }
  }
 }
 MeshNormals {
  283;
  -0.000000;0.980789;-0.195073;,
  -0.000000;0.923893;-0.382652;,
  -0.000000;0.831495;-0.555533;,
  0.000001;0.707140;-0.707074;,
  0.000002;0.555604;-0.831447;,
  0.000001;0.382712;-0.923868;,
  -0.000000;0.195108;-0.980782;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.195108;-0.980782;,
  0.000001;-0.382712;-0.923868;,
  0.000002;-0.555604;-0.831447;,
  0.000001;-0.707140;-0.707074;,
  -0.000000;-0.831495;-0.555533;,
  -0.000000;-0.923893;-0.382652;,
  -0.000000;-0.980789;-0.195073;,
  -0.038055;0.980789;-0.191326;,
  -0.074651;0.923892;-0.375300;,
  -0.108380;0.831495;-0.544858;,
  -0.137943;0.707141;-0.693486;,
  -0.162207;0.555604;-0.815471;,
  -0.180238;0.382711;-0.906116;,
  -0.191341;0.195108;-0.961936;,
  -0.195090;0.000000;-0.980785;,
  -0.191341;-0.195107;-0.961937;,
  -0.180236;-0.382711;-0.906116;,
  -0.162206;-0.555605;-0.815471;,
  -0.137943;-0.707141;-0.693486;,
  -0.108380;-0.831495;-0.544858;,
  -0.074652;-0.923893;-0.375299;,
  -0.038057;-0.980789;-0.191325;,
  -0.074651;0.980789;-0.180224;,
  -0.146434;0.923892;-0.353525;,
  -0.212593;0.831495;-0.513245;,
  -0.270585;0.707142;-0.653249;,
  -0.318181;0.555604;-0.768157;,
  -0.353548;0.382711;-0.853543;,
  -0.375327;0.195108;-0.906125;,
  -0.382682;0.000000;-0.923880;,
  -0.375328;-0.195106;-0.906125;,
  -0.353548;-0.382711;-0.853543;,
  -0.318181;-0.555605;-0.768156;,
  -0.270585;-0.707142;-0.653249;,
  -0.212593;-0.831495;-0.513245;,
  -0.146434;-0.923892;-0.353525;,
  -0.074651;-0.980789;-0.180224;,
  -0.108378;0.980789;-0.162197;,
  -0.212590;0.923892;-0.318164;,
  -0.308637;0.831495;-0.461909;,
  -0.392828;0.707141;-0.587909;,
  -0.461926;0.555605;-0.691323;,
  -0.513272;0.382712;-0.768169;,
  -0.544891;0.195108;-0.815491;,
  -0.555569;0.000000;-0.831470;,
  -0.544892;-0.195107;-0.815491;,
  -0.513273;-0.382712;-0.768168;,
  -0.461927;-0.555605;-0.691322;,
  -0.392828;-0.707141;-0.587909;,
  -0.308637;-0.831495;-0.461909;,
  -0.212589;-0.923892;-0.318164;,
  -0.108376;-0.980789;-0.162197;,
  -0.137938;0.980789;-0.137938;,
  -0.270576;0.923892;-0.270576;,
  -0.392822;0.831495;-0.392820;,
  -0.499976;0.707141;-0.499975;,
  -0.587921;0.555605;-0.587921;,
  -0.653273;0.382712;-0.653273;,
  -0.693518;0.195107;-0.693517;,
  -0.707108;0.000000;-0.707106;,
  -0.693518;-0.195107;-0.693517;,
  -0.653273;-0.382712;-0.653273;,
  -0.587921;-0.555605;-0.587921;,
  -0.499976;-0.707141;-0.499975;,
  -0.392821;-0.831495;-0.392820;,
  -0.270577;-0.923892;-0.270576;,
  -0.137938;-0.980789;-0.137938;,
  -0.162197;0.980789;-0.108378;,
  -0.318164;0.923892;-0.212590;,
  -0.461910;0.831495;-0.308636;,
  -0.587910;0.707142;-0.392826;,
  -0.691323;0.555605;-0.461926;,
  -0.768168;0.382712;-0.513273;,
  -0.815491;0.195107;-0.544892;,
  -0.831470;0.000000;-0.555569;,
  -0.815491;-0.195107;-0.544892;,
  -0.768168;-0.382712;-0.513273;,
  -0.691323;-0.555605;-0.461926;,
  -0.587910;-0.707142;-0.392826;,
  -0.461910;-0.831495;-0.308636;,
  -0.318165;-0.923892;-0.212590;,
  -0.162197;-0.980789;-0.108378;,
  -0.180224;0.980789;-0.074651;,
  -0.353525;0.923892;-0.146435;,
  -0.513246;0.831494;-0.212593;,
  -0.653250;0.707141;-0.270584;,
  -0.768156;0.555605;-0.318180;,
  -0.853543;0.382711;-0.353548;,
  -0.906125;0.195108;-0.375328;,
  -0.923879;0.000000;-0.382683;,
  -0.906125;-0.195108;-0.375328;,
  -0.853543;-0.382711;-0.353548;,
  -0.768156;-0.555605;-0.318180;,
  -0.653250;-0.707141;-0.270584;,
  -0.513246;-0.831495;-0.212593;,
  -0.353525;-0.923892;-0.146435;,
  -0.180224;-0.980789;-0.074651;,
  -0.191325;0.980789;-0.038058;,
  -0.375300;0.923892;-0.074653;,
  -0.544859;0.831494;-0.108380;,
  -0.693486;0.707141;-0.137944;,
  -0.815471;0.555605;-0.162206;,
  -0.906117;0.382711;-0.180236;,
  -0.961936;0.195109;-0.191340;,
  -0.980786;0.000000;-0.195089;,
  -0.961936;-0.195109;-0.191340;,
  -0.906117;-0.382711;-0.180236;,
  -0.815470;-0.555605;-0.162206;,
  -0.693486;-0.707141;-0.137944;,
  -0.544858;-0.831495;-0.108380;,
  -0.375300;-0.923892;-0.074651;,
  -0.191325;-0.980789;-0.038055;,
  -0.195037;0.980608;-0.019212;,
  -0.382381;0.923237;-0.037663;,
  -0.554704;0.830252;-0.054634;,
  -0.705365;0.705432;-0.069472;,
  -0.828673;0.553751;-0.081615;,
  -0.920067;0.381137;-0.090617;,
  -0.976237;0.194205;-0.096149;,
  -0.995185;0.000000;-0.098014;,
  -0.976237;-0.194205;-0.096149;,
  -0.920067;-0.381137;-0.090617;,
  -0.828673;-0.553751;-0.081615;,
  -0.705365;-0.705432;-0.069472;,
  -0.554703;-0.830253;-0.054634;,
  -0.382381;-0.923237;-0.037661;,
  -0.195037;-0.980608;-0.019208;,
  0.000000;-0.998015;-0.062982;,
  0.195037;0.980608;-0.019208;,
  0.382380;0.923237;-0.037660;,
  0.554704;0.830252;-0.054634;,
  0.705365;0.705431;-0.069474;,
  0.828673;0.553751;-0.081619;,
  0.920066;0.381138;-0.090619;,
  0.976238;0.194204;-0.096151;,
  0.995185;0.000000;-0.098018;,
  0.976238;-0.194204;-0.096151;,
  0.920066;-0.381138;-0.090619;,
  0.828673;-0.553751;-0.081619;,
  0.705365;-0.705432;-0.069472;,
  0.554703;-0.830253;-0.054631;,
  0.382382;-0.923237;-0.037659;,
  0.195037;-0.980608;-0.019208;,
  0.191325;0.980789;-0.038056;,
  0.375300;0.923892;-0.074652;,
  0.544858;0.831494;-0.108381;,
  0.693487;0.707140;-0.137944;,
  0.815471;0.555604;-0.162207;,
  0.906116;0.382713;-0.180237;,
  0.961936;0.195108;-0.191341;,
  0.980785;0.000000;-0.195090;,
  0.961936;-0.195108;-0.191341;,
  0.906116;-0.382712;-0.180237;,
  0.815471;-0.555604;-0.162207;,
  0.693487;-0.707140;-0.137943;,
  0.544858;-0.831495;-0.108379;,
  0.375300;-0.923892;-0.074651;,
  0.191325;-0.980789;-0.038056;,
  0.180225;0.980789;-0.074651;,
  0.353525;0.923892;-0.146435;,
  0.513246;0.831494;-0.212594;,
  0.653250;0.707140;-0.270586;,
  0.768156;0.555605;-0.318181;,
  0.853542;0.382713;-0.353549;,
  0.906124;0.195107;-0.375329;,
  0.923879;0.000000;-0.382683;,
  0.906124;-0.195107;-0.375329;,
  0.853542;-0.382713;-0.353549;,
  0.768156;-0.555605;-0.318181;,
  0.653249;-0.707141;-0.270587;,
  0.513245;-0.831495;-0.212595;,
  0.353525;-0.923892;-0.146436;,
  0.180224;-0.980789;-0.074652;,
  0.162197;0.980789;-0.108378;,
  0.318164;0.923892;-0.212590;,
  0.461910;0.831494;-0.308637;,
  0.587910;0.707140;-0.392829;,
  0.691322;0.555606;-0.461927;,
  0.768168;0.382713;-0.513273;,
  0.815491;0.195107;-0.544892;,
  0.831471;0.000000;-0.555568;,
  0.815491;-0.195107;-0.544892;,
  0.768168;-0.382713;-0.513273;,
  0.691322;-0.555606;-0.461927;,
  0.587910;-0.707141;-0.392829;,
  0.461908;-0.831495;-0.308637;,
  0.318163;-0.923892;-0.212592;,
  0.162197;-0.980789;-0.108378;,
  0.137938;0.980789;-0.137938;,
  0.270576;0.923892;-0.270576;,
  0.392822;0.831494;-0.392821;,
  0.499977;0.707140;-0.499976;,
  0.587921;0.555606;-0.587921;,
  0.653273;0.382714;-0.653272;,
  0.693518;0.195108;-0.693517;,
  0.707107;0.000000;-0.707107;,
  0.693518;-0.195108;-0.693517;,
  0.653273;-0.382714;-0.653272;,
  0.587921;-0.555606;-0.587921;,
  0.499976;-0.707140;-0.499976;,
  0.392821;-0.831495;-0.392820;,
  0.270577;-0.923892;-0.270576;,
  0.137939;-0.980789;-0.137937;,
  0.108377;0.980789;-0.162197;,
  0.212591;0.923892;-0.318164;,
  0.308638;0.831494;-0.461909;,
  0.392829;0.707140;-0.587910;,
  0.461927;0.555606;-0.691322;,
  0.513273;0.382713;-0.768168;,
  0.544892;0.195107;-0.815491;,
  0.555568;0.000000;-0.831471;,
  0.544892;-0.195107;-0.815491;,
  0.513273;-0.382713;-0.768168;,
  0.461927;-0.555606;-0.691322;,
  0.392828;-0.707141;-0.587910;,
  0.308638;-0.831495;-0.461908;,
  0.212592;-0.923892;-0.318163;,
  0.108377;-0.980789;-0.162197;,
  0.000000;0.998015;-0.062982;,
  0.074651;0.980789;-0.180224;,
  0.146435;0.923892;-0.353525;,
  0.212595;0.831494;-0.513246;,
  0.270586;0.707141;-0.653250;,
  0.318181;0.555606;-0.768156;,
  0.353549;0.382712;-0.853542;,
  0.375329;0.195107;-0.906124;,
  0.382684;0.000000;-0.923879;,
  0.375329;-0.195107;-0.906124;,
  0.353549;-0.382712;-0.853542;,
  0.318181;-0.555606;-0.768156;,
  0.270587;-0.707141;-0.653249;,
  0.212596;-0.831494;-0.513245;,
  0.146436;-0.923892;-0.353525;,
  0.074651;-0.980789;-0.180225;,
  0.038057;0.980789;-0.191325;,
  0.074652;0.923893;-0.375299;,
  0.108381;0.831494;-0.544859;,
  0.137945;0.707140;-0.693487;,
  0.162208;0.555605;-0.815470;,
  0.180238;0.382713;-0.906116;,
  0.191341;0.195108;-0.961936;,
  0.195091;0.000000;-0.980785;,
  0.191341;-0.195108;-0.961936;,
  0.180238;-0.382713;-0.906116;,
  0.162208;-0.555605;-0.815470;,
  0.137945;-0.707140;-0.693487;,
  0.108381;-0.831495;-0.544858;,
  0.074652;-0.923893;-0.375299;,
  0.038057;-0.980789;-0.191325;,
  -0.619529;-0.781116;0.077727;,
  0.619529;-0.781116;0.077727;,
  -0.619529;0.781116;0.077727;,
  0.619529;0.781116;0.077727;,
  -0.996310;-0.000000;0.085830;,
  0.996310;-0.000001;0.085830;,
  0.000001;0.000000;1.000000;,
  0.000000;-0.997699;0.067806;,
  -0.000001;-0.000000;-1.000000;,
  0.000000;0.997699;0.067806;,
  0.000001;-0.000000;1.000000;,
  0.000001;0.000001;1.000000;,
  0.000002;-0.000000;1.000000;,
  -0.000001;-0.000000;-1.000000;,
  -0.000001;-0.000001;-1.000000;,
  -0.000001;-0.000001;-1.000000;,
  -0.000002;0.000000;-1.000000;,
  -0.000001;-0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000001;-0.000001;-1.000000;,
  -0.000001;-0.000001;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000001;-0.000001;1.000000;,
  0.000002;-0.000001;1.000000;,
  -0.000001;-0.000001;-1.000000;;
  272;
  4;7,22,21,6;,
  4;5,20,19,4;,
  4;3,18,17,2;,
  4;14,29,28,13;,
  4;1,16,15,0;,
  4;12,27,26,11;,
  4;10,25,24,9;,
  4;8,23,22,7;,
  4;6,21,20,5;,
  4;4,19,18,3;,
  4;2,17,16,1;,
  4;13,28,27,12;,
  4;11,26,25,10;,
  4;9,24,23,8;,
  4;17,32,31,16;,
  4;28,43,42,27;,
  4;26,41,40,25;,
  4;24,39,38,23;,
  4;22,37,36,21;,
  4;20,35,34,19;,
  4;18,33,32,17;,
  4;29,44,43,28;,
  4;16,31,30,15;,
  4;27,42,41,26;,
  4;25,40,39,24;,
  4;23,38,37,22;,
  4;21,36,35,20;,
  4;19,34,33,18;,
  4;32,47,46,31;,
  4;43,58,57,42;,
  4;41,56,55,40;,
  4;39,54,53,38;,
  4;37,52,51,36;,
  4;35,50,49,34;,
  4;33,48,47,32;,
  4;44,59,58,43;,
  4;31,46,45,30;,
  4;42,57,56,41;,
  4;40,55,54,39;,
  4;38,53,52,37;,
  4;36,51,50,35;,
  4;34,49,48,33;,
  4;47,62,61,46;,
  4;58,73,72,57;,
  4;56,71,70,55;,
  4;54,69,68,53;,
  4;52,67,66,51;,
  4;50,65,64,49;,
  4;48,63,62,47;,
  4;59,74,73,58;,
  4;46,61,60,45;,
  4;57,72,71,56;,
  4;55,70,69,54;,
  4;53,68,67,52;,
  4;51,66,65,50;,
  4;49,64,63,48;,
  4;62,77,76,61;,
  4;73,88,87,72;,
  4;71,86,85,70;,
  4;69,84,83,68;,
  4;67,82,81,66;,
  4;65,80,79,64;,
  4;63,78,77,62;,
  4;74,89,88,73;,
  4;61,76,75,60;,
  4;72,87,86,71;,
  4;70,85,84,69;,
  4;68,83,82,67;,
  4;66,81,80,65;,
  4;64,79,78,63;,
  4;77,92,91,76;,
  4;88,103,102,87;,
  4;86,101,100,85;,
  4;84,99,98,83;,
  4;82,97,96,81;,
  4;80,95,94,79;,
  4;78,93,92,77;,
  4;89,104,103,88;,
  4;76,91,90,75;,
  4;87,102,101,86;,
  4;85,100,99,84;,
  4;83,98,97,82;,
  4;81,96,95,80;,
  4;79,94,93,78;,
  4;92,107,106,91;,
  4;103,118,117,102;,
  4;101,116,115,100;,
  4;99,114,113,98;,
  4;97,112,111,96;,
  4;95,110,109,94;,
  4;93,108,107,92;,
  4;104,119,118,103;,
  4;91,106,105,90;,
  4;102,117,116,101;,
  4;100,115,114,99;,
  4;98,113,112,97;,
  4;96,111,110,95;,
  4;94,109,108,93;,
  4;107,122,121,106;,
  4;118,133,132,117;,
  4;116,131,130,115;,
  4;114,129,128,113;,
  4;112,127,126,111;,
  4;110,125,124,109;,
  4;108,123,122,107;,
  4;119,134,133,118;,
  4;106,121,120,105;,
  4;117,132,131,116;,
  4;115,130,129,114;,
  4;113,128,127,112;,
  4;111,126,125,110;,
  4;109,124,123,108;,
  4;138,153,152,137;,
  4;149,164,163,148;,
  4;147,162,161,146;,
  4;145,160,159,144;,
  4;143,158,157,142;,
  4;141,156,155,140;,
  4;139,154,153,138;,
  4;150,165,164,149;,
  4;137,152,151,136;,
  4;148,163,162,147;,
  4;146,161,160,145;,
  4;144,159,158,143;,
  4;142,157,156,141;,
  4;140,155,154,139;,
  4;153,168,167,152;,
  4;164,179,178,163;,
  4;162,177,176,161;,
  4;160,175,174,159;,
  4;158,173,172,157;,
  4;156,171,170,155;,
  4;154,169,168,153;,
  4;165,180,179,164;,
  4;152,167,166,151;,
  4;163,178,177,162;,
  4;161,176,175,160;,
  4;159,174,173,158;,
  4;157,172,171,156;,
  4;155,170,169,154;,
  4;168,183,182,167;,
  4;179,194,193,178;,
  4;177,192,191,176;,
  4;175,190,189,174;,
  4;173,188,187,172;,
  4;171,186,185,170;,
  4;169,184,183,168;,
  4;180,195,194,179;,
  4;167,182,181,166;,
  4;178,193,192,177;,
  4;176,191,190,175;,
  4;174,189,188,173;,
  4;172,187,186,171;,
  4;170,185,184,169;,
  4;183,198,197,182;,
  4;194,209,208,193;,
  4;192,207,206,191;,
  4;190,205,204,189;,
  4;188,203,202,187;,
  4;186,201,200,185;,
  4;184,199,198,183;,
  4;195,210,209,194;,
  4;182,197,196,181;,
  4;193,208,207,192;,
  4;191,206,205,190;,
  4;189,204,203,188;,
  4;187,202,201,186;,
  4;185,200,199,184;,
  4;198,213,212,197;,
  4;209,224,223,208;,
  4;207,222,221,206;,
  4;205,220,219,204;,
  4;203,218,217,202;,
  4;201,216,215,200;,
  4;199,214,213,198;,
  4;210,225,224,209;,
  4;197,212,211,196;,
  4;208,223,222,207;,
  4;206,221,220,205;,
  4;204,219,218,203;,
  4;202,217,216,201;,
  4;200,215,214,199;,
  4;213,229,228,212;,
  4;224,240,239,223;,
  4;222,238,237,221;,
  4;220,236,235,219;,
  4;218,234,233,217;,
  4;216,232,231,215;,
  4;214,230,229,213;,
  4;225,241,240,224;,
  4;212,228,227,211;,
  4;223,239,238,222;,
  4;221,237,236,220;,
  4;219,235,234,218;,
  4;217,233,232,216;,
  4;215,231,230,214;,
  4;229,244,243,228;,
  4;240,255,254,239;,
  4;238,253,252,237;,
  4;236,251,250,235;,
  4;234,249,248,233;,
  4;232,247,246,231;,
  4;230,245,244,229;,
  4;241,256,255,240;,
  4;228,243,242,227;,
  4;239,254,253,238;,
  4;237,252,251,236;,
  4;235,250,249,234;,
  4;233,248,247,232;,
  4;231,246,245,230;,
  3;135,29,14;,
  3;0,15,226;,
  3;15,30,226;,
  3;135,44,29;,
  3;30,45,226;,
  3;135,59,44;,
  3;45,60,226;,
  3;135,74,59;,
  3;60,75,226;,
  3;135,89,74;,
  3;75,90,226;,
  3;135,104,89;,
  3;90,105,226;,
  3;135,119,104;,
  3;105,120,226;,
  3;135,134,119;,
  3;136,151,226;,
  3;135,165,150;,
  3;151,166,226;,
  3;135,180,165;,
  3;166,181,226;,
  3;135,195,180;,
  3;181,196,226;,
  3;135,210,195;,
  3;196,211,226;,
  3;135,225,210;,
  3;211,227,226;,
  3;135,241,225;,
  3;227,242,226;,
  3;135,256,241;,
  4;244,2,1,243;,
  4;255,13,12,254;,
  3;242,0,226;,
  4;253,11,10,252;,
  4;251,9,8,250;,
  4;249,7,6,248;,
  4;247,5,4,246;,
  4;245,3,2,244;,
  4;256,14,13,255;,
  4;243,1,0,242;,
  4;254,12,11,253;,
  4;252,10,9,251;,
  4;250,8,7,249;,
  4;248,6,5,247;,
  4;246,4,3,245;,
  3;135,14,256;,
  4;264,264,258,258;,
  4;266,260,260,266;,
  4;267,263,268,269;,
  4;262,262,260,260;,
  4;270,265,271,272;,
  4;259,259,261,261;,
  4;273,274,265,270;,
  4;261,261,257,257;,
  4;275,276,263,267;,
  4;258,258,262,262;,
  4;265,277,278,271;,
  4;259,266,266,259;,
  4;279,275,267,280;,
  4;280,267,269,281;,
  4;274,282,277,265;,
  4;257,257,264,264;;
 }
 MeshTextureCoords {
  301;
  0.175850;0.193880;,
  0.170910;0.216970;,
  0.150890;0.213140;,
  0.152880;0.193800;,
  0.133880;0.193750;,
  0.132480;0.210460;,
  0.114950;0.208110;,
  0.116090;0.193620;,
  0.098690;0.193450;,
  0.097700;0.205730;,
  0.080250;0.203140;,
  0.081090;0.193240;,
  0.305840;0.307810;,
  0.301810;0.310580;,
  0.285540;0.291880;,
  0.293080;0.286040;,
  0.062760;0.193020;,
  0.062120;0.200180;,
  0.042810;0.196740;,
  0.043170;0.192830;,
  0.278650;0.265250;,
  0.268470;0.274500;,
  0.250510;0.258770;,
  0.262200;0.245940;,
  0.243620;0.228600;,
  0.231640;0.244920;,
  0.211920;0.233140;,
  0.222930;0.213720;,
  0.200270;0.201890;,
  0.191540;0.223690;,
  0.078010;0.212890;,
  0.060350;0.207210;,
  0.279270;0.298780;,
  0.260170;0.284740;,
  0.241090;0.272110;,
  0.222000;0.260950;,
  0.202910;0.251290;,
  0.183890;0.243150;,
  0.165090;0.236540;,
  0.146740;0.231260;,
  0.129140;0.226710;,
  0.112040;0.222370;,
  0.095120;0.217850;,
  0.298410;0.314040;,
  0.041770;0.200540;,
  0.074360;0.222360;,
  0.057460;0.213940;,
  0.274340;0.306510;,
  0.253610;0.295760;,
  0.233550;0.285890;,
  0.214100;0.276890;,
  0.195180;0.268740;,
  0.176740;0.261360;,
  0.158760;0.254670;,
  0.141230;0.248470;,
  0.124190;0.242460;,
  0.107500;0.236310;,
  0.090960;0.229720;,
  0.295730;0.318040;,
  0.040060;0.204120;,
  0.069270;0.231450;,
  0.053450;0.220260;,
  0.270780;0.314890;,
  0.248700;0.307440;,
  0.227660;0.300150;,
  0.207580;0.293030;,
  0.188340;0.286060;,
  0.169840;0.279170;,
  0.151960;0.272280;,
  0.134640;0.265250;,
  0.117800;0.257890;,
  0.101360;0.249970;,
  0.085220;0.241250;,
  0.293840;0.322450;,
  0.037710;0.207390;,
  0.062700;0.239990;,
  0.048330;0.225980;,
  0.268630;0.323770;,
  0.245430;0.319740;,
  0.223310;0.315060;,
  0.202260;0.309730;,
  0.182190;0.303800;,
  0.163000;0.297240;,
  0.144610;0.290020;,
  0.126930;0.282060;,
  0.109920;0.273250;,
  0.093550;0.263420;,
  0.077800;0.252400;,
  0.292790;0.327150;,
  0.034780;0.210220;,
  0.054560;0.247820;,
  0.042100;0.230940;,
  0.267960;0.333000;,
  0.243870;0.332650;,
  0.220540;0.330780;,
  0.198110;0.327390;,
  0.176620;0.322530;,
  0.156090;0.316230;,
  0.136520;0.308520;,
  0.117930;0.299390;,
  0.100350;0.288820;,
  0.083850;0.276740;,
  0.068540;0.263090;,
  0.292630;0.331980;,
  0.031300;0.212510;,
  0.044740;0.254690;,
  0.034810;0.234880;,
  0.268900;0.342420;,
  0.244210;0.346150;,
  0.219560;0.347560;,
  0.195290;0.346490;,
  0.171680;0.342910;,
  0.148990;0.336870;,
  0.127450;0.328460;,
  0.107270;0.317760;,
  0.088670;0.304890;,
  0.071880;0.289970;,
  0.057160;0.273160;,
  0.293370;0.336800;,
  0.027380;0.214140;,
  0.033140;0.260220;,
  0.026550;0.237550;,
  0.271560;0.351820;,
  0.246760;0.360160;,
  0.220800;0.365610;,
  0.194190;0.367600;,
  0.167570;0.365810;,
  0.141620;0.360160;,
  0.117010;0.350760;,
  0.094340;0.337850;,
  0.074190;0.321800;,
  0.057050;0.303090;,
  0.043300;0.282320;,
  0.295030;0.341450;,
  0.023120;0.215000;,
  0.034970;0.124030;,
  0.046490;0.130280;,
  0.035540;0.150120;,
  0.027150;0.147080;,
  0.267350;0.038800;,
  0.265220;0.047760;,
  0.241830;0.045040;,
  0.243900;0.031870;,
  0.219690;0.027180;,
  0.218640;0.044120;,
  0.195780;0.045260;,
  0.194780;0.025260;,
  0.169920;0.027190;,
  0.173440;0.048470;,
  0.151930;0.053800;,
  0.145760;0.031680;,
  0.122140;0.039390;,
  0.131150;0.061190;,
  0.111310;0.070800;,
  0.099560;0.050570;,
  0.079550;0.065550;,
  0.092670;0.082470;,
  0.075530;0.096310;,
  0.061760;0.082560;,
  0.046670;0.102230;,
  0.059990;0.112250;,
  0.290080;0.047410;,
  0.288740;0.051930;,
  0.027480;0.171190;,
  0.023140;0.170250;,
  0.056110;0.137660;,
  0.042840;0.154370;,
  0.264700;0.056740;,
  0.241810;0.057820;,
  0.219710;0.060010;,
  0.198410;0.063400;,
  0.177850;0.067860;,
  0.158160;0.073670;,
  0.139200;0.080700;,
  0.120950;0.089070;,
  0.103360;0.098680;,
  0.086660;0.109960;,
  0.070840;0.122890;,
  0.288290;0.056570;,
  0.031440;0.172900;,
  0.064010;0.145870;,
  0.049010;0.159570;,
  0.265700;0.065530;,
  0.243620;0.070100;,
  0.222520;0.075010;,
  0.202370;0.080310;,
  0.182990;0.085890;,
  0.164440;0.092090;,
  0.146520;0.098850;,
  0.129160;0.106260;,
  0.112170;0.114320;,
  0.095700;0.123530;,
  0.079630;0.133950;,
  0.288700;0.061190;,
  0.034930;0.175260;,
  0.070320;0.154670;,
  0.054030;0.165480;,
  0.268120;0.073970;,
  0.247070;0.081840;,
  0.226890;0.089300;,
  0.207520;0.096410;,
  0.188820;0.103100;,
  0.170790;0.109750;,
  0.153290;0.116310;,
  0.136250;0.122950;,
  0.119460;0.129710;,
  0.102970;0.137150;,
  0.086620;0.145350;,
  0.289960;0.065640;,
  0.037860;0.178150;,
  0.075140;0.163930;,
  0.057920;0.171930;,
  0.271900;0.081910;,
  0.252140;0.093020;,
  0.232810;0.103070;,
  0.213910;0.112100;,
  0.195400;0.120020;,
  0.177320;0.127240;,
  0.159620;0.133700;,
  0.142320;0.139590;,
  0.125350;0.145190;,
  0.108640;0.150910;,
  0.091980;0.157050;,
  0.292020;0.069790;,
  0.040190;0.181460;,
  0.078530;0.173520;,
  0.060680;0.178750;,
  0.277010;0.089200;,
  0.258840;0.103580;,
  0.240380;0.116420;,
  0.221720;0.127680;,
  0.202940;0.137180;,
  0.184160;0.145230;,
  0.165550;0.151690;,
  0.147450;0.156740;,
  0.129800;0.160910;,
  0.112750;0.164900;,
  0.095770;0.169010;,
  0.294820;0.073500;,
  0.041870;0.185080;,
  0.080510;0.183320;,
  0.062300;0.185820;,
  0.283410;0.095660;,
  0.267290;0.113400;,
  0.249880;0.129410;,
  0.231300;0.143380;,
  0.211900;0.155230;,
  0.191570;0.164540;,
  0.171010;0.171130;,
  0.151280;0.174780;,
  0.132800;0.177120;,
  0.115230;0.179160;,
  0.097990;0.181160;,
  0.298290;0.076660;,
  0.042880;0.188910;,
  0.317570;0.330090;,
  0.021940;0.192750;,
  0.312340;0.057000;,
  0.291080;0.101060;,
  0.277670;0.122250;,
  0.261760;0.141980;,
  0.243420;0.159590;,
  0.222820;0.174600;,
  0.200100;0.186300;,
  0.302350;0.079130;,
  0.721870;0.445940;,
  0.838430;0.922420;,
  0.762050;0.939940;,
  0.673610;0.456850;,
  0.500910;0.472480;,
  0.550380;0.471650;,
  0.578840;0.961940;,
  0.500490;0.963000;,
  0.849890;0.187070;,
  0.721410;0.187420;,
  0.770300;0.096220;,
  0.849580;0.073660;,
  0.612290;0.466670;,
  0.670850;0.954320;,
  0.335360;0.186450;,
  0.499930;0.187210;,
  0.499290;0.327210;,
  0.392540;0.302280;,
  0.451450;0.471560;,
  0.422140;0.961800;,
  0.330140;0.954020;,
  0.389540;0.466480;,
  0.393600;0.071160;,
  0.500580;0.047220;,
  0.238960;0.939490;,
  0.328230;0.456550;,
  0.850200;0.300470;,
  0.770800;0.278350;,
  0.664510;0.187970;,
  0.606260;0.303270;,
  0.929480;0.277920;,
  0.978370;0.186710;,
  0.928980;0.095780;,
  0.607330;0.072150;,
  0.162620;0.921840;,
  0.280000;0.445560;;
 }
}
