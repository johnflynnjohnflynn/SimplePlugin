
SimplePlugin
------------

### Bare bones audio plugin with auto-created, generic GUI using JUCE.

![SimplePlugin image](http://www.johnflynn.info/images/SimplePlugin.png)

Good example if you've looked at the JUCE tutorials/example plugins and are wondering how to utilise the AudioProcessorParameter class heirarchy.

- Specify parameters only in processor constructor.
- Automatically handles GUI sliders and creates a simple generic editor.

To implement parameters are created on the heap rather than the stack. A view container 'params' is kept for easy access (and to remove the need to dynamic_cast), before adding the parameters to the plugin using addParameter() as usual.

See [www.johnflynn.info](http://www.johnflynn.info/)
