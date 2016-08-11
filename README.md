
##先说一说项目中为什么需要使用AFNetworking，使用时又为什么需要封装
每一款APP的开发，都需要用到网络请求接口，如果使用iOS系统原生的NSURLConnection，既考验开发人员的技术功底（那得是技术相当滴硬，而且在这方面造诣也很高），又考验开发人员的忍耐力（不停地改，改，改），后期维护也需要大量耗费人力和时间。于是AFNetworking出世了（目前来说比较安全，比较专业，还免费），但是直接调用其API也不太好，无法做到整个项目的统一配置，最好的方式就是对网络层（AFNetworking）再封装一层，整个项目不允许直接使用 AFNetworking 的 API ，而是直接调用自己封装的网路层，这样网络请求需求都可以在这一层里配置好，使用者无须知道里面的代码逻辑，只管调用封装好的方法就可以实现对应需求。

**封装优势：**

 1. 降低项目中的耦合
 2. 统一配置，方便后期维护。

**Request_method的规则：**
 * GET：获取资源，不会改动资源
 * POST：创建记录
 * PATCH：改变资源状态或更新部分属性
 * PUT：更新全部属性
 * DELETE：删除资源

###以下是几种常用的网络请求方式
**pragma mark - GET 请求网络数据**
```
/**
 *  请求网络数据
 *  @param path             请求的地址
 *  @param paramters        请求的参数
 *  @param downLoadProgress 进度
 *  @param success          请求成功的回调
 *  @param failure          请求失败的回调
 */
+ (void)requestGETDataWithPath:(NSString *)path
                 withParamters:(NSDictionary *)paramters
                  withProgress:(void(^) (float progress))downLoadProgress
                       success:(void(^) (BOOL isSuccess, id responseObject))success
                       failure:(void(^) (NSError *error))failure  {
    [[NetWorkingManager shareManager] GET:path parameters:paramters progress:^(NSProgress * _Nonnull downloadProgress) {
        NSLog(@"downLoadProcess = %@",downLoadProgress);
        if (downloadProgress) {
            downLoadProgress(downloadProgress.completedUnitCount / downloadProgress.totalUnitCount);
        }
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSLog(@"responseObject = %@",responseObject);
        if (success) {   
            success(YES,responseObject);
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"error = %@",error);
        if (failure) {
            failure(error);
        }
    }];   
 }
```
**pragma mark - POST 传送网络数据**
```
/**
 *  传送网络数据
 *
 *  @param path           请求的地址
 *  @param paramters      请求的参数
 *  @param uploadProgress 进度
 *  @param success        请求成功的回调
 *  @param failure        请求失败的回调
 */
+ (void)sendPOSTDataWithPath:(NSString *)path
               withParamters:(NSDictionary *)paramters
                withProgress:(void(^) (float progress))upLoadProgress
                     success:(void(^) (BOOL isSuccess, id responseObject))success
                     failure:(void(^) (NSError *error))failure {
    [[NetWorkingManager shareManager] POST:path parameters:paramters progress:^(NSProgress * _Nonnull uploadProgress) {
        NSLog(@"downLoadProcess = %@",uploadProgress);
        if (uploadProgress) {
            upLoadProgress(uploadProgress.completedUnitCount / uploadProgress.totalUnitCount);
        }
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSLog(@"responseObject = %@",responseObject);
        if (success) {
            success(YES,responseObject);
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"error = %@",error);
        if (failure) {
            failure(error);
        }
    }];
}
```
**pragma mark - 取消网络请求--指定请求**
```
/**
 *  取消指定的url请求
 *  @param type 该请求的请求类型
 *  @param path 该请求的完整url
 */
+(void)cancelHttpRequestWithType:(NSString *)type WithPath:(NSString *)path {
    NSError * error;
    // 根据请求的类型 以及 请求的url创建一个NSMutableURLRequest---通过该url去匹配请求队列中是否有该url,如果有的话 那么就取消该请求
    NSString * urlToPeCanced = [[[[NetWorkingManager shareManager].requestSerializer requestWithMethod:type URLString:path parameters:nil error:&error] URL] path];
    for (NSOperation * operation in [NetWorkingManager shareManager].operationQueue.operations) {
        // 如果是请求队列
        if ([operation isKindOfClass:[NSURLSessionTask class]]) {
            // 请求的类型匹配
            BOOL hasMatchRequestType = [type isEqualToString:[[(NSURLSessionTask *)operation currentRequest] HTTPMethod]];
            // 请求的url匹配
            BOOL hasMatchRequestUrlString = [urlToPeCanced isEqualToString:[[[(NSURLSessionTask *)operation currentRequest] URL] path]];
            // 两项都匹配的话  取消该请求
            if (hasMatchRequestType&&hasMatchRequestUrlString) {
                [operation cancel];
            }
        }
    }
}
```
###这里就不一一列举了，如果有你需要的可以根据下载地址下载demo（https://github.com/FlyJing/AFNetWorking-.git）

```
#pragma mark - GET 请求网络数据
/**
 *  请求网络数据
 *
 *  @param path             请求的地址
 *  @param paramters        请求的参数
 *  @param downLoadProgress 进度
 *  @param success          请求成功的回调
 *  @param failure          请求失败的回调
 */
+ (void)requestGETDataWithPath:(NSString *)path
                 withParamters:(NSDictionary *)paramters
                  withProgress:(void(^) (float progress))downLoadProgress
                       success:(void(^) (BOOL isSuccess, id responseObject))success
                       failure:(void(^) (NSError *error))failure ;

#pragma mark - POST 传送网络数据
/**
 *  传送网络数据
 *
 *  @param path           请求的地址
 *  @param paramters      请求的参数
 *  @param uploadProgress 进度
 *  @param success        请求成功的回调
 *  @param failure        请求失败的回调
 */
+ (void)sendPOSTDataWithPath:(NSString *)path
               withParamters:(NSDictionary *)paramters
                withProgress:(void(^) (float progress))upLoadProgress
                     success:(void(^) (BOOL isSuccess, id responseObject))success
                     failure:(void(^) (NSError *error))failure ;

#pragma mark POST 上传图片
/**
 *  上传图片
 *
 *  @param path           上传的地址--需要填写完整的url
 *  @param paramters      上传图片预留参数--根据具体需求而定，可以出
 *  @param imageArray     上传的图片数组
 *  @param width          图片要被压缩到的宽度
 *  @param upLoadProgress 进度
 *  @param success        请求成功的回调
 *  @param failure        请求失败的回调
 */
+ (void)sendPOSTImageWithPath:(NSString *)path
               withParamters:(NSDictionary *)paramters
              withImageArray:(NSArray *)imageArray
             withtargetWidth:(CGFloat )width
                withProgress:(void(^) (float progress))upLoadProgress
                     success:(void(^) (BOOL isSuccess, id responseObject))success
                     failure:(void(^) (NSError *error))failure ;

#pragma mark POST 上传视频
/**
 *  上传视频
 *
 *  @param path           上传的地址--需要填写完整的url
 *  @param videoPath      上传的视频--本地沙盒的路径
 *  @param paramters      上传视频预留参数--根据具体需求而定，可以出
 *  @param upLoadProgress 进度
 *  @param success        请求成功的回调
 *  @param failure        请求失败的回调
 */
+ (void)sendPOSTImageWithPath:(NSString *)path
                withVideoPath:(NSString *)videoPath
                withParamters:(NSDictionary *)paramters
                 withProgress:(void(^) (float progress))upLoadProgress
                      success:(void(^) (BOOL isSuccess, id responseObject))success
                      failure:(void(^) (NSError *error))failure ;

#pragma mark DOWNLOAD 文件下载
+ (void)requestDownLoadDataWithPath:(NSString *)path
                      withParamters:(NSDictionary *)paramters
                       withSavaPath:(NSString *)savePath
                       withProgress:(void(^) (float progress))downLoadProgress
                            success:(void(^) (BOOL isSuccess, id responseObject))success
                            failure:(void(^) (NSError *error))failure ;

#pragma mark - DELETE 删除资源
+ (void)requestDELETEDataWithPath:(NSString *)path
                    withParamters:(NSDictionary *)paramters
                          success:(void (^) (BOOL isSuccess, id responseObject))success
                          failure:(void (^) (NSError *error))failure ;

#pragma mark - PUT 更新全部属性
+ (void)sendPUTDataWithPath:(NSString *)path
              withParamters:(NSDictionary *)paramters
                    success:(void(^) (BOOL isSuccess, id responseObject))success
                    failure:(void(^) (NSError *error))failure ;

#pragma  mark - PATCH 改变资源状态或更新部分属性
+ (void)sendPATCHDataWithPath:(NSString *)path
                withParamters:(NSDictionary *)paramters
                      success:(void (^) (BOOL isSuccess, id responseObject))success
                      failure:(void (^) (NSError *error))failure ;

#pragma mark - 取消网络请求--全部请求
+ (void)cancelAllNetworkRequest ;

#pragma mark - 取消网络请求--指定请求
/**
 *  取消指定的url请求
 *
 *  @param type 该请求的请求类型
 *  @param path 该请求的完整url
 */
+(void)cancelHttpRequestWithType:(NSString *)type WithPath:(NSString *)path ;
```

在这个demo里面我大概封装了10中网络请求方式，其中有3-4种方式是大家常用的，其余的是可能会遇到的，总地来说看看是没有损失的。这10种方式有的是我在项目中用到过的，有的是我借鉴网上的资源，如有不足的地方希望你可以提出来我们探讨，最好在github上给我提一个PR。

PS:如果觉得对你有使用价值请在该页面右上角的Star上面轻轻点一下，如果你对这个demo有更好的见解请提交一个PR，同时在该页面右上角的Star上面轻轻点一下下。会不定期更新demo，可能是完善AFNetworking封装，也可能是其他第三方封装。

Contact This is according to the relevant information on the apple official documentation and making do some summary, if you found inaccurate or have new Suggestions can contact me WeChat: cz192230531, or to carry my PR in the making, welcome to contact.
