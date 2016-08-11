//
//  UIImage+Compression.h
//  AFNetWorking二次封装
//
//  Created by Jing  on 16/8/11.
//  Copyright © 2016年 Jing . All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (Compression)
/**
 *  图片压缩
 *
 *  @param sourceImg   被压缩的图片
 *  @param defineWidth 被压缩的尺寸(宽)
 *
 *  @return 被压缩的图片
 */
+(UIImage *)imageCompressed:(UIImage *)sourceImage withdefineWidth:(CGFloat)defineWidth ;
@end
