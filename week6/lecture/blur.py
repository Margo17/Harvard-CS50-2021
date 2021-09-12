from PIL import Image, ImageFilter

before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(10)) # BoxBlur parameter changes blur intensity
after.save("out.bmp")