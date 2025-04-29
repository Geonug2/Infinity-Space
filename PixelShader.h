#ifndef PIXELSHADER_H
#define PIXELSHADER_H

#include <d3d11.h>
#include <wrl/client.h>
#include <string>

// PixelShader klass tegeleb HLSL faili kompileerimise ja pixel shaderi loomisega.
class PixelShader {
public:
    PixelShader();
    ~PixelShader();

    // Algseadistab shaderi, kasutades seadme viidet ja shaderi faili teed.
    bool Initialize(ID3D11Device* device, const std::wstring& shaderPath);

    // Seob kompileeritud pixel shaderi antud seadme konteksti
    void Bind(ID3D11DeviceContext* deviceContext);

private:
    // Kasutame ComPtr-i, et lihtsustada COM objektide haldust.
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
};

#endif // PIXELSHADER_H
