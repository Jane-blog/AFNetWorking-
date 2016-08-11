# AFNetWorking二次封装
这里针对AFN3.X版本进行了一下二次封装，降低项目中的耦合，方便后期维护。
#项目中为什么使用AFNetworking，为什么需要封装
每一款APP的开发，都需要用到网络请求接口，如果使用iOS系统原生的NSURLConnection，既考验开发人员的技术功底（那得是技术相当滴硬，而且在这方面造诣也很高），又考验开发人员的忍耐力（不停地改，改，改），后期维护也是很耗费人力和时间。于是AFNetworking出世了（目前来说比较安全，比较专业，还免费），但是直接调用其API也不太好，无法做到整个项目的统一配置，最好的方式就是对网络层（AFNetworking）再封装一层，整个项目不允许直接使用 AFNetworking 的 API ，而是直接调用自己封装的网路层，这样网络配置都可以在这一层里配置好，使用者无须知道里面的代码逻辑，只管调用封装好的方法就可以了。

**这里先讲述一下网络请求规则**
 * GET：获取资源，不会改动资源
 * POST：创建记录
 * PATCH：改变资源状态或更新部分属性
 * PUT：更新全部属性
 * DELETE：删除资源

##以下是几种常用的网络请求方式
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
```

```
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
```

```
#pragma mark - DELETE 删除资源
+ (void)requestDELETEDataWithPath:(NSString *)path
                    withParamters:(NSDictionary *)paramters
                          success:(void (^) (BOOL isSuccess, id responseObject))success
                          failure:(void (^) (NSError *error))failure ;
```
在这个demo里面我大概封装了10中网络请求方式，其中有3-4种方式是大家常用的，其余的是可能会遇到的，总地来说看看是没有损失的。这10种方式有的是我在项目中用到过的，有的是我借鉴网上的资源，如有不足的地方希望你可以提出来我们探讨，最好在github上给我提一个PR。
PS:如果觉得对你有使用价值请在该页面右上角的Star上面轻轻点一下，如果你对这个demo有更好的见解请提交一个PR，同时在该页面右上角的Star上面轻轻点一下下。会不定期更新demo，可能是完善AFNetworking封装，也可能是其他第三方封装。

Contact This is according to the relevant information on the apple official documentation and making do some summary, if you found inaccurate or have new Suggestions can contact me WeChat: cz192230531, or to carry my PR in the making, welcome to contact.
