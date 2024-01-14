# _Look Me in the Eyes I_
~ artistic explanation here ~
<br><br><br>
## Technical Approach
_Look Me in the Eyes I_ is an image processor that rearranges or "remixes" the pixels of an source image to resemble a target image as closely as possible. I chose to accomplish this through the use of [openFrameworks](https://openframeworks.cc), an open source C++ toolkit for creative coding.
### Target Image Pixel Sorting
In computer memory, pixels for grayscale images are stored as an array of values where each pixel is represented by a single 8-bit number from 0 (black) to 255 (white) that looks something like this:
```
[  215  ,  125  ,  86  ,  35  ,  202  ,  174  ]
|______||______||_____||_____||_______||______|
 pixel0  pixel1  pixel2 pixel3  pixel4  pixel5

```
For color images, pixels are still stored as an array of 8-bit numbers, but now each pixel takes up three indexes for red, green, and blue values like so:
```
[  215  ,  125  ,  86  ,  35  ,  202  ,  174  ]
|______________________||_____________________|
   red    green   blue    red   green    blue

          pixel0                pixel1
```
Similarly, some images also use a fourth index for an "alpha" (opacity) channel. <br><br>
The best way to create a remix of the source image that closely resembles the target image is to map the pixels according to brightness. Therefore, I needed to know in what order the pixels were in terms of their brightness. For grayscale images, the brightness is just the pixel value itself and for color images it is an average of the red, green, and blue values. To sort the pixels, I chose to use an algorithm called [counting sort](https://www.geeksforgeeks.org/counting-sort/). This algorithm does not sort based on comparisons, so it is linear on the input size and range of inputs (O(n+k) where n is the input size and k is the range of input values). Since the range of brightness is small (0-255) in comparison with the number of pixels in an image (786,432 in a 1024x768 image), this is a very efficient algorithm to use for our purposes. To preserve the original indexes of each pixels, the array I sorted by brightness contained entries that were structs consisting of both the brightness and original index.

### Source Image Pixel Sorting
### Pixel Mapping


## Results

This project is a part of DART 496, an image/video processing and remix theory independent study with [Professor Eduardo Navas](http://navasse.net/docs/index.php). Resources used for _Look Me in the Eyes I_ include the [openFrameworks graphics documentation](https://openframeworks.cc/documentation/graphics/) and the chapter ["Image Processing and Computer Vision" from _ofBook_](https://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html)
