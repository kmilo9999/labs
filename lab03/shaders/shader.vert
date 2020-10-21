#version 330 core

layout(location = 0) in vec3 ObjectSpace_position; // object-space vertex position
layout(location = 1) in vec3 ObjectSpace_normal;   // object-space vertex normal

uniform mat4 model, view, projection;
out vec3 FragPos;
out vec3 Normal;
out vec3 viewPos;
void main() {
    FragPos = vec3(model * vec4(ObjectSpace_position, 1.0));
    Normal = ObjectSpace_normal;
    mat4 invView = inverse(view);
    viewPos = vec3(invView * vec4(0.0,0.0,0.0,1.0)).xyz;

    //viewPos.x = view[0][3];
   // viewPos.y = view[1][3];
   // viewPos.z = view[2][3];

    gl_Position = projection * view  * vec4(FragPos, 1.0);
}
