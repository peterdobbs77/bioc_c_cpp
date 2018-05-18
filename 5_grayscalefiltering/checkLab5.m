%read in a binary image.  Change the file name as needed
im_spatial=readFloat('grayScale_noise_output.bin', 256, 256);
%view the image
imagesc(im_spatial); colormap(gray); axis image; axis off;
