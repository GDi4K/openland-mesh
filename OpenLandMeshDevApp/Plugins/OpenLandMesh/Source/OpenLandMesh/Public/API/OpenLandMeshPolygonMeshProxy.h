﻿// Copyright (c) 2021 Arunoda Susiripala. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include <functional>

#include "Types/OpenLandMeshInfo.h"
#include "Core/OpenLandPolygonMesh.h"
#include "UObject/Object.h"
#include "OpenLandMeshPolygonMeshProxy.generated.h"

struct FOpenLandBuildMeshResultCacheInfo {
	FString CacheKey;
	FOpenLandPolygonMeshBuildResultPtr MeshBuildResult;
	FDateTime CachedAt;
	FDateTime LastCacheHitAt;
	bool IsModifying = false;
};
/**
 * 
 */
UCLASS()
class OPENLANDMESH_API UOpenLandMeshPolygonMeshProxy : public UObject
{
	GENERATED_BODY()

	FOpenLandPolygonMesh* PolygonMesh;
	static TMap<FString, FOpenLandBuildMeshResultCacheInfo> CachedBuildMesh;

public:
	UOpenLandMeshPolygonMeshProxy();
	~UOpenLandMeshPolygonMeshProxy();

	FOpenLandPolygonMeshBuildResultPtr BuildMesh(UObject* WorldContext, FOpenLandPolygonMeshBuildOptions Options, FString CacheKey="") const;
	void BuildMeshAsync(UObject* WorldContext, FOpenLandPolygonMeshBuildOptions Options,
	                    std::function<void(FOpenLandPolygonMeshBuildResultPtr)> Callback) const;
	void ModifyVertices(::UObject* WorldContext, FOpenLandPolygonMeshBuildResultPtr MeshBuildResult,
	                    FOpenLandPolygonMeshModifyOptions Options) const;
	// Here we do vertex modifications outside of the game thread
	// The return boolean value indicates whether we should render the Target MeshInfo or not
	// Note: It's very important to pass the same Target all the time because the return value is related to something happens earlier.
	FOpenLandPolygonMeshModifyStatus StartModifyVertices(UObject* WorldContext, FOpenLandPolygonMeshBuildResultPtr MeshBuildResult,
	                         FOpenLandPolygonMeshModifyOptions Options) const;
	FOpenLandPolygonMeshModifyStatus CheckModifyVerticesStatus(float LastFrameTime) const;

	void RegisterVertexModifier(function<FVertexModifierResult(FVertexModifierPayload)> Callback);
	FGpuComputeMaterialStatus RegisterGpuVertexModifier(FComputeMaterial VertexModifier);
	int32 CalculateVerticesForSubdivision(int32 Subdivision) const;

	// Blueprint Methods
	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	UOpenLandMeshPolygonMeshProxy* AddTriFace(const FVector A, const FVector B, const FVector C);

	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	UOpenLandMeshPolygonMeshProxy* AddQuadFace(const FVector A, const FVector B, const FVector C, const FVector D);

	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	UOpenLandMeshPolygonMeshProxy* Transform(const FTransform Tranformer);

	// Static Methods
	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	static UOpenLandMeshPolygonMeshProxy* MakeEmptyPolygonMesh();

	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	static UOpenLandMeshPolygonMeshProxy* MakePlaneMesh();

	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	static UOpenLandMeshPolygonMeshProxy* MakeCubeMesh();

	UFUNCTION(BlueprintCallable, Category=OpenLandMesh)
	static UOpenLandMeshPolygonMeshProxy* MakePyramidMesh();
};
