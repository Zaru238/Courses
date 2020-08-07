function [  ] = drawPts( img, pts )
hold off
imagesc(img);
colormap gray
hold on
plot(pts(:,1), pts(:,2), 'ro','LineWidth',2)
end

