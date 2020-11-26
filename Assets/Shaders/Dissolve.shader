Shader "Custom/Dissolve"
{
    Properties
    {
        [HDR]_GlowColour ("Glow Colour", Color) = (1,1,1,1)
        _MainTex ("First Texture (RGB)", 2D) = "white" {}
        _MainGlossiness ("First Smoothness", Range(0,1)) = 0.5
        _MainMetallic ("First Metallic", Range(0,1)) = 0.0
        _SecondaryTex ("Second Texture (RGB)", 2D) = "white" {}
        _SecondaryGlossiness ("Second Smoothness", Range(0,1)) = 0.5
        _SecondaryMetallic ("Second Metallic", Range(0,1)) = 0.0
        _NoiseTex ("Dissolve Guide (BW)", 2D) = "white" {}
        _DissolveThreshold ("Blend", Range(0,1)) = 0.0
        _GlowStep ("Glow Size", float) = 0.0
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows
        #pragma target 3.0


        struct Input
        {
            float2 uv_MainTex;
        };

        sampler2D _MainTex;
        half _MainGlossiness;
        half _MainMetallic;

        sampler2D _SecondaryTex;
        half _SecondaryMetallic;
        half _SecondaryGlossiness;

        sampler2D _NoiseTex;
        half _DissolveThreshold;
        half _GlowStep;
        fixed4 _GlowColour;

        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            fixed4 Noise = tex2D( _NoiseTex, IN.uv_MainTex );
            float DissolveAmount = ( Noise.r - _DissolveThreshold );

            //clip( DissolveAmount );

            float1 IsVisible = step( DissolveAmount, _GlowStep );
            float1 IsMasked = DissolveAmount >= -_GlowStep;

            float4 Emission = _GlowColour * ( IsVisible * _DissolveThreshold) * IsMasked;
            
            fixed4 First = tex2D (_MainTex, IN.uv_MainTex);
            fixed4 Second = tex2D (_SecondaryTex, IN.uv_MainTex);
            o.Albedo = lerp(First.rgb, Second.rgb, step( DissolveAmount, 0 ) );
            o.Metallic = lerp(_MainMetallic, _SecondaryMetallic, step( DissolveAmount, 0 ) );;
            o.Smoothness = lerp(_MainGlossiness, _SecondaryGlossiness, step( DissolveAmount, 0 ) );;;
            o.Emission = Emission;
            o.Alpha = First.a;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
