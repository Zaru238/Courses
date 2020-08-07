%% by Jakob Engel
%% warp img2 to fit the projection function of img1

img2_dist = imreadbw('img2.jpg');
img1_dist = imreadbw('img1.jpg');

K1 = [ 388.6795 0  343.7415;
       0  389.4250 234.6182;
       0 0 1];

K2 = [279.7399 0 347.32012;
     0 279.7399 234.99819;
     0 0 1];

 K1I = K1^-1;
 
% get coordinate list
x = repmat(1:752,480,1);
y = repmat(1:480,752,1)';
xw = x;
yw = y;

% multiply each point with K1I and project (division by 1)
x = K1I(1,1) * x + K1I(1,3);
y = K1I(2,2) * y + K1I(2,3);

% get radius of each point
r = (x.^2 + y.^2).^0.5;

% calc inv of f1, and new radius.
r1 = tan(0.926464 * r) / (2 * tan(0.926464 / 2));

% calc f2, and new radius
r2 = r1 .* (1 - 0.3407*r1 + 0.057*r1.^2 - 0.0046 * r1.^3 + 0.00014 * r1.^4);

% multiply with K2 & change radius
xw = K2(1,1) * x .* r2 ./ r + K2(1,3);
yw = K2(2,2) * y .* r2 ./ r + K2(2,3);

% interpolate
img1_undist = interp2(img2_dist, xw+1, yw+1);

subplot(1,3,1)
imagesc(img2_dist) % img 2
colormap gray
axis equal
subplot(1,3,2)
imagesc(img1_undist) % img 2 warped to fit img1's projection model
colormap gray
axis equal
subplot(1,3,3)
imagesc(img1_dist) % img 1
colormap gray
axis equal
