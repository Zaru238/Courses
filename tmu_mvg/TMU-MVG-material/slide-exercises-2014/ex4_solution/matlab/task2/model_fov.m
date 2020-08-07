function img_undist = model_fov(img_dist, calib, f_new)
%close all
% K = [ 388.6795 0  343.7415;
%        0  389.4250 234.6182;
%        0 0 1];

fx = calib(1);
fy = calib(2);
cx = calib(3);
cy = calib(4);
s = calib(5);
   
K = [640 * fx, 0, 640 * cx;
    0,  480 * fy, 480 * cy;
    0 0 1];

hight = 480;
width = 640;

KNew = [f_new 0 width/2;
        0 f_new hight/2;
        0.0 0.0 1.0];
    
KNewI = KNew^-1;

% get coordinate list
x = repmat(1:width,hight,1);
y = repmat(1:hight,width,1)';
xw = zeros(hight,width);
yw = zeros(hight,width);

% multiply each point with KNewI and project (division by 1)
x = KNewI(1,1) * x + KNewI(1,3);
y = KNewI(2,2) * y + KNewI(2,3);

% get radius of each point
r = (x.^2 + y.^2).^0.5;

% calc f
f = atan(2 * r * tan(s / 2)) ./ (s * r);

% this only works, as f(isnan(f)) is a 1x1 matrix (there is at most one
% point exactly with raidus=0).
f(isnan(f)) = 0;

% multiply with K
xw = K(1,1) * x .* f + K(1,3);
yw = K(2,2) * y .* f + K(2,3);

% interpolate
img_undist = interp2(img_dist, xw+1, yw+1, 'linear', 0);

%subplot(1,2,1)
% figure
% imagesc(img_dist)
% colormap gray
% axis equal
% figure
% imagesc(img_undist)
% colormap gray
% axis equal
%subplot(1,2,2)

