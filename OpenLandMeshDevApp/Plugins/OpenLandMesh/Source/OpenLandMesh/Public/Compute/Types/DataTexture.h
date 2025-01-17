﻿// Copyright (c) 2021 Arunoda Susiripala. All Rights Reserved.

#pragma once

#include "RHI.h"

class OPENLANDMESH_API FDataTexture
{
	int32 TextureWidth = 0;
	uint8* SourceData = nullptr;

	UPROPERTY(Transient);
	UTexture2D* Texture = nullptr;

	FUpdateTextureRegion2D WholeTextureRegion;

public:

	FDataTexture(int TextureWidth);
	~FDataTexture();

	// Getters
	int32 GetTextureWidth() const { return TextureWidth; }
	UTexture2D* GetTexture() const { return Texture; }

	// Methods
	void SetPixelValue(int32 Index, uint8 R, uint8 G, uint8 B, uint8 A);
	void SetFloatValue(int32 Index, float Value);
	void Reset();
	void UpdateTexture();
};
