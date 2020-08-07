%% by Jakob Engel
%% image 1
img_dist = imreadbw('img1.jpg');

K = [ 388.6795 0  343.7415;
       0  389.4250 234.6182;
       0 0 1];


KNew = [250 0.0 512;
        0 250 384;
        0.0 0.0 1.0];
    
xw = zeros(768,1024);
yw = zeros(768,1024);

KNewI = KNew^-1;
for x=1:1024
    for y=1:768
        % un-project:
        p = KNewI * [x-1;y-1;1];
        
        % do perspective projection
        pp = p(1:2) / p(3);

        % get radius
        radius = norm(pp);

        if(radius == 0)
            f = 1;
        else
            f = atan(2 * radius * tan(0.926464 / 2)) / (0.926464*radius);
        end
        
        % calculate new point
        p = K * [f * pp; 1];
        
        % save result
        xw(y, x) = p(1);
        yw(y, x) = p(2);
    end
    x
end

img_undist = interp2(img_dist, xw+1, yw+1);

subplot(1,2,1)
imagesc(img_undist)
colormap gray
axis equal
subplot(1,2,2)
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
    

xw = zeros(768,1024);
yw = zeros(768,1024);

KNewI = KNew^-1;
for x=1:1024
    for y=1:768
        % un-project:
        p = KNewI * [x-1;y-1;1];
        
        % do perspective projection
        pp = p(1:2) / p(3);

        % get radius
        radius = norm(pp);

        % calculate f(radius)
        f = (1 - 0.3407*radius + 0.057*radius^2 - 0.0046 * radius^3 + 0.00014 * radius^4);

        % calculate new point
        p = K * [pp * f; 1];
        
        % save result
        xw(y, x) = p(1);
        yw(y, x) = p(2);
    end
    x
end

img_undist = interp2(img_dist, xw+1, yw+1);

subplot(1,2,1)
imagesc(img_undist)
colormap gray
axis equal
subplot(1,2,2)
imagesc(img_dist)
colormap gray
axis equal
