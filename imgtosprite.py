from PIL import Image as image
import sys,getopt
	#args: file, transparent_r, transparent_g, transparent_b, x, y, width, height, filename

def colorint(colortuple):
	return colortuple[0]/8 + colortuple[1]/8*32 + colortuple[2]/8*1024

def main(argv):
	img = image.open(argv[0])
	r,g,b = int(argv[1]), int(argv[2]), int(argv[3])
	x = int(argv[4])
	y = int(argv[5])
	width = int(argv[6])
	height = int(argv[7])
	filename = argv[8]
	print "r %i" % r
	print "g %i" % g
	print "b %i" % b
	print "x %i" % x
	print "y %i" % y
	print "width %i" % width
	print "height %i" % height
	palette = [(r,g,b)]
	pix = img.load()
	palettized = []
	print "whoo"
	for dy in range(height):
		row = []
		for dx in range(width):
			color = pix[x+dx,y+dy]
			try:
				idx = palette.index(color)
			except ValueError:
				idx = len(palette)
				palette.append(color)
			row.append(idx)
		palettized.append(row)
		
	bytes = []
	for spritex in range(width/8):
		for spritey in range(height/8):
			for row in range(8):
				highbyte = 0
				lowbyte = 0
				for col in range(8):
					paletteindex = palettized[spritex*8+row][spritey*8+col]
					print "paletteindex: %i" % paletteindex
					if  paletteindex > 1:
						highbyte = highbyte * 2 + 1
					else:
						highbyte = highbyte * 2
					if paletteindex % 2 == 1:
						lowbyte = lowbyte * 2 + 1
					else:
						lowbyte = lowbyte * 2
				bytes.append(highbyte)
				bytes.append(lowbyte)
	print bytes
	palette.append((0,0,0))
	palette.append((0,0,0))
	palette.append((0,0,0))
	print (colorint(palette[0]), colorint(palette[2]), colorint(palette[1]), colorint(palette[3]))
	
					
		
if __name__ == "__main__":
	main(sys.argv[1:])
	
