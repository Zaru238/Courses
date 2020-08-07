% (b) -----------------------------------------
function W = projection_parallel(V,f)


nVertices = size(V,1);

% Conversion to homogenous coordinates:
Vh = [V,ones(nVertices,1)];

% Translate the vertices to the camera coordinate system:
T = [1 0  0 0 ; 0 1 0 0 ; 0 0 1 1];
Vh = T * Vh';

% Project the vertices:
K = [f 0 0; 0 f 0; 0 0 1];
Wh_t = K * Vh;
Wh = Wh_t';

% Back transform from homogenous to 3D coordinates:
W = Wh(:,1:2);