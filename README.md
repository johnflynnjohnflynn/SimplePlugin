    SimplePlugin
    ------------
    
    ### Bare bones audio plugin with default generic GUI using JUCE.
    
    - Need specify parameters only in processor constructor.
    - Automatically handles GUI sliders and creates a simple generic editor.
    
    To implement our parameters are created on the heap rather than the stack.
    We keep a view container 'params' for easy access (and to remove the need to
    dynamic_cast), before adding the parameters to the plugin using 
    addParameter() as usual.
    
    Our generic GUI editor accesses the params through public getParam() function 
    and should change a parameter value only through the public writeParam().
