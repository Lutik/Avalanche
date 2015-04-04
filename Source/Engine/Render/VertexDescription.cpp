#include "stdafx.h"
#include "VertexDescription.h"

void VertexDescription::AddAttrib(const VertexAttribute& attr)
{
	_attribs.push_back(attr);
}

void VertexDescription::Apply() const
{
	for(const VertexAttribute &attr : _attribs)
	{
		glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, vertexSize, (void*)attr.offset);
		glEnableVertexAttribArray(attr.location);
	}
}