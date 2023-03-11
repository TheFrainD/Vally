#include "Material.h"

namespace Vally
{
	void Material::Bind() const noexcept
	{
		if (m_shader)
		{
			m_shader->Use();

			if (m_textures.m_albedo)
			{
				m_textures.m_albedo->Bind();
			}
		}
	}
}
