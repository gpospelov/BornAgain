#ifndef EDITORHELPER_H
#define EDITORHELPER_H

class EditorHelper
{
public:

    static int getLayerHeight() { return m_default_layer_height; }
    static int getLayerWidth() { return m_default_layer_width; }

    static int getMultiLayerHeight() { return m_default_layer_height; }
    static int getMultiLayerWidth() { return m_default_layer_width*1.20; }

    private:
    static int m_default_layer_height;
    static int m_default_layer_width;
};

#endif // EDITORHELPER_H
