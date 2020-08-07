%% prepare files
camera = 'L';
path = 'E:\\data\\data1223';
list_file = sprintf('%s\\%s_List.txt', path, camera);
fid = fopen(list_file);
files = textscan(fid, '%s');
n_files = length(files{1});

%% undistortion
if camera == 'L'
    calib = [0.494332 0.6595 0.513371 0.52721 1.01136]; % L
elseif camera == 'R'
    calib = [0.491196 0.656008 0.52112 0.526148 1.00786]; % R
else
    error('Please select L or R camera!')
end
f_new = 150;

for i = 1:n_files
    filename = sprintf('%s\\%s\\%s', path, camera, files{1}{i});
    new_filename = sprintf('%s\\%s_undist\\%s', path, camera, files{1}{i});
    image = imreadbw(filename);
    imshow(image);
    image_undist = model_fov(image, calib, f_new);

    imwrite(image_undist, new_filename);
end