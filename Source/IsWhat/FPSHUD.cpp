// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSHUD.h"




void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		// 找到画布中心。
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// 纹理维度一半偏移，使纹理中心和画布中心对齐。
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		// 在中心点绘制准星。
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::Red);
		/*
		 平铺项目使用大小从纹理。 
	 *
	 * @param	InPosition		Draw position  绘制位置 
	 * @param	InTexture		The texture  纹理 
		
		FCanvasTileItem( const FVector2D& InPosition, const FTexture* InTexture, const FLinearColor& InColor );
		
		FCanvasTileItem::FCanvasTileItem(const FVector2D& InPosition, const FTexture* InTexture, const FLinearColor& InColor)
			: FCanvasItem(InPosition)
			, Z(1.0f)
			, UV0(0.0f, 0.0f)
			, UV1(1.0f, 1.0f)
			, Texture(InTexture)
			, MaterialRenderProxy(nullptr)
			, Rotation(ForceInitToZero)
			, PivotPoint(FVector2D::ZeroVector)
		{
			SetColor(InColor);
			// Ensure texture is valid.
			check(InTexture);
			Size.X = InTexture->GetSizeX();
			Size.Y = InTexture->GetSizeY();
		}
		
		*/



		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
		/*
		
		void UCanvas::DrawItem( class FCanvasItem& Item )
		{
			Canvas->DrawItem( Item );
		}
		
		
		*/



	}
}