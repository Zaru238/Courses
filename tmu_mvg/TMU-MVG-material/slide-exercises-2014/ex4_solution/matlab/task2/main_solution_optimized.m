%% by Jakob Engel
%% image 1
img_dist = imreadbw('img1.jpg');

K = [ 388.6795 0  343.7415;
       0  389.4250 234.6182;
       0 0 1];


KNew = [250 0.0 512;
        0 250 384;
        0.0 0.0 1.0];
    
KNewI = KNew^-1;

% get coordinate list
x = repmat(1:1024,768,1);
y = repmat(1:768,1024,1)';
xw = zeros(768,1024);
yw = zeros(768,1024);

% multiply each point with KNewI and project (division by 1)
x = KNewI(1,1) * x + KNewI(1,3);
y = KNewI(2,2) * y + KNewI(2,3);

% get radius of each point
r = (x.^2 + y.^2).^0.5;

% calc f
f = atan(2 * r * tan(0.926464 / 2)) ./ (0.926464*r);

% this only works, as f(isnan(f)) is a 1x1 matrix (there is at most one
% point exactly with raidus=0).
f(isnan(f)) = 0;

% multiply with K
xw = K(1,1) * x .* f + K(1,3);
yw = K(2,2) * y .* f + K(2,3);

% interpolate
img_undist = interp2(img_dist, xw+1, yw+1);

%subplot(1,2,1)
imagesc(img_undist)
colormap gray
axis equal
%subplot(1,2,2)
figure
imagesc(img_dist)
colormap gray
axis equal

%% image 2

img_dist = imreadbw('img2.jpg');

K = [279.7399 0 347.32012;
     0 279.7399 234.99819;
     0 0 1];

 

KNew = [200 0.0 512;
        0 200 384;
        0.0 0.0 1.0];
    
    
% get coordinate list
x = repmat(1:1024,768,1);
y = repmat(1:768,1024,1)';
xw = zeros(768,1024);
yw = zeros(768,1024);

% multiply each point with KNewI and project (division by 1)
x = KNewI(1,1) * x + KNewI(1,3);
y = KNewI(2,2) * y + KNewI(2,3);

% get radius of each point
r = (x.^2 + y.^2).^0.5;

% calc f
f = (1 - 0.3407*r + 0.057*r.^2 - 0.0046 * r.^3 + 0.00014 * r.^4);

% multiply with K
xw = K(1,1) * x .* f + K(1,3);
yw = K(2,2) * y .* f + K(2,3);

% interpolate
img_undist = interp2(img_dist, xw+1, yw+1);

img_undist = interp2(img_dist, xw+1, yw+1);

subplot(1,2,1)
imagesc(img_undist)
colormap gray
axis equal
subplot(1,2,2)
imagesc(img_dist)
colormap gray
axis equal
