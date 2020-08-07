%% prepare files
path = 'E:\Hardware\Inutive\read_RGBD\read_RGBD\calibration_inuitive\images_inuitive_color_fisheye';
list_file = sprintf('%s\\list.txt', path);
fid = fopen(list_file);
files = textscan(fid, '%s');
n_files = length(files{1});

%% undistortion

calib = [0.407173 0.543773 0.501359 0.491671 0.920029]; % L

f_new = 150;

for i = 1:n_files
    filename = sprintf('%s\\%s', path, files{1}{i});
    new_filename = sprintf('%s\\undist\\%s', path, files{1}{i});
    image = imreadbw(filename);
    %imshow(image);
    image_undist = model_fov(image, calib, f_new);
    imwrite(image_undist, new_filename);
end