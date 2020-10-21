#version 400
// TODO: Make a new in vec3 with the same name as the vertex shader's output (Task 12)
in vec3 out_color;
out vec3 fragColor;

void main(){
    fragColor = out_color;
    // TODO: Set fragColor to the color input variable. (Task 12)
}
