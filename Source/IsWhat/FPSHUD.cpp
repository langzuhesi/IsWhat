// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSHUD.h"




void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		// �ҵ��������ġ�
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// ����ά��һ��ƫ�ƣ�ʹ�������ĺͻ������Ķ��롣
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		// �����ĵ����׼�ǡ�
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::Red);
		/*
		 ƽ����Ŀʹ�ô�С������ 
	 *
	 * @param	InPosition		Draw position  ����λ�� 
	 * @param	InTexture		The texture  ���� 
		
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