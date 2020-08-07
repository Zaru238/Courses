% Exercise Sheet 4, Part II
%
% ========================================
% Image Formation, Exercise 1
% ========================================
%
% (a) -----------------------------------------
function W = projection_perspective(V,f)

% Conversion to homogenous coordinates:
nVertices = size(V,1);
Vh = [V,ones(nVertices,1)];

% Translate the vertices to the camera coordinate system:
T = [1 0  0 0 ; 0 1 0 0 ; 0 0 1 1];
Vh = T * Vh';

% Project the vertices:
K = [f 0 0 ; 0 f 0 ; 0 0 1];
Wh_t = K * Vh;
Wh = Wh_t';

% project onto image plane
W = Wh(:,1:2) ./ Wh(:,[3,3]);
