﻿// Copyright (c) 2021 Arunoda Susiripala. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "OpenLandInstancingRules.generated.h"

UENUM(BlueprintType)
enum EOpenLandInstancingRuleObjectType
{
	IROT_ACTOR=0 UMETA(DisplayName="Actor"),
	IROT_STATIC_MESH=1 UMETA(DisplayName="Static Mesh")
};

UENUM()
enum EOpenLandInstancingRuleSamplingAlgorithm
{
	IRSA_MODIFIED_POISSON_2D=0  UMETA(DisplayName="Modified Poisson 2D"),
	IRSA_VERTICES=1 UMETA(DisplayName="Pick Vertices"),
	IRSA_CENTROID=2 UMETA(DisplayName="Pick Centroids"),
	IRSA_ORIGIN=3 UMETA(DisplayName="Use Origin"),
	IRSA_MOVE_TO_X_AXIS=4 UMETA(DisplayName="Move to X Axis"),
	IRSA_MOVE_TO_Y_AXIS=5 UMETA(DisplayName="Move to Y Axis"),
	IRSA_MOVE_TO_Z_AXIS=6 UMETA(DisplayName="Move to Z Axis")
};

UENUM(BlueprintType)
enum EOpenLandInstancingTangentXGeneration
{
	ITG_FROM_UVS=0 UMETA(DisplayName="From UVs"),
	ITG_TO_PIVOT=1 UMETA(DisplayName="To Pivot"),
	ITG_TO_CENTER=2 UMETA(DisplayName="To Center")
};

USTRUCT(BlueprintType)
struct FOpenLandInstancingRuleRandomScaleUniform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	float Min = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	float Max = 1.0f;
};

USTRUCT(BlueprintType)
struct FOpenLandInstancingRuleRandomScale3D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Min = {1.0f, 1.0f, 1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Max = {1.0f, 1.0f, 1.0f};
};

USTRUCT(BlueprintType)
struct FOpenLandInstancingRuleRandomRotation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Min = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Max = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	bool bUseLocalRotation = true;
};

USTRUCT(BlueprintType)
struct FOpenLandInstancingRuleRandomDisplacement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Min = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FVector Max = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	bool bUseLocalDisplacement = true;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOpenLandInstancingRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	TEnumAsByte<EOpenLandInstancingRuleObjectType> PlacementObject = IROT_STATIC_MESH;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing",  meta = (EditCondition = "PlacementObject==0", AllowedClasses="Actor"))
	UClass* Actor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing",  meta = (EditCondition = "PlacementObject==1"))
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	TEnumAsByte<EOpenLandInstancingRuleSamplingAlgorithm> SamplingAlgorithm = IRSA_MODIFIED_POISSON_2D;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing", meta = (EditCondition = "SamplingAlgorithm==0"))
	float Density = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing", meta = (EditCondition = "SamplingAlgorithm==0"))
	float MinimumDistance = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing", meta = (EditCondition = "SamplingAlgorithm!=3"))
	int32 DesiredLODIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing",  meta = (EditCondition = "PlacementObject==1"))
	bool bEnableCollisions = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	TEnumAsByte<EOpenLandInstancingTangentXGeneration> CalculateTangentX = ITG_FROM_UVS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FOpenLandInstancingRuleRandomScaleUniform RandomScaleUniform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FOpenLandInstancingRuleRandomScale3D RandomScale3D;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FOpenLandInstancingRuleRandomRotation RandomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenLandMesh Instancing")
	FOpenLandInstancingRuleRandomDisplacement RandomDisplacement;
};
