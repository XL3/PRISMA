#version 330
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;

out vec2 v_texcoord;
out vec3 v_normal;
out vec3 v_view;
out vec3 v_world;

uniform mat4 M;
uniform mat4 M_it;
uniform mat4 VP;
uniform vec3 cam_position;

void main(){
    vec4 world = M * vec4(position, 1.0f);

    gl_Position = VP * world;

    v_texcoord = texcoord;
    v_normal = (M_it * vec4(normal, 0.0f)).xyz;
    v_view = cam_position - world.xyz;
    v_world = world.xyz;
}
