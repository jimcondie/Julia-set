# Julia-set

the parameters are set in the text file.  For example,

1500 1500 100000 -1 0 0 1 0 1

Image Width pixels
Image Height pixels
maxiter
C Real Part
C Imaginary Part  (f(z)=z^2+C)
MinX
MaxX
MinY
MaxY (z=x+i*y)

the first two numbers are the # of pixels.  the maxiter is maximum iterations per pixel. the next two numbers define the complex number, C.  the last 4 numbers set the window to be plotted. 

interesting values for C:
  C=0 yields a unit circle, 
  C=i yields an interesting strand
  C=-1 gives a nice pattern

