
#include "pbPlots.h"
#include "supportLib.h"

//gcc plots/plots.c plots/pbPlots.c plots/supportLib.c -lm

int main(){
	int size=13;
	double xs [] = {0, 3,3,5,5,9,9,12,12,20,20,39,39};
	double ys [] = {0, 0,1,1,2,2,3,3,1,1,4,4,4};
	_Bool success;

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlot(canvasReference, 600, 400, xs, size, ys, size, errorMessage);

    if(success){
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasReference->image);
        WriteToFile(pngdata, length, "example1.png");
        DeleteImage(canvasReference->image);
	}else{
	    fprintf(stderr, "Error: ");
	    for(int i = 0; i < errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

	return success ? 0 : 1;
}
