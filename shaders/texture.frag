#version 330
precision highp float;

in vec4 v_color;
in vec2 v_texcoord; // texture coordinates received from the vertex shader

out vec4 color;

uniform vec4 tint;
uniform sampler2D texture_sampler; // the sampler using which we will sample colors from the texture 


void main(){
    color = (tint * v_color);
    color = texture(texture_sampler, v_texcoord) * color;
}
