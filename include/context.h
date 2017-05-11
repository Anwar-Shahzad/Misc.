#ifndef __CONTEXT__
#define __CONTEXT__

class Context{
    //Maintain state if needed

public:
	int height = 480; // for example
	int width = 640; // for example
	bool use_average = false;
	bool use_flip = false;
	bool use_invert = false;
	
};

#endif
