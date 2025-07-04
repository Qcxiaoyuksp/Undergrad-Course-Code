<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>字典目录管理</title>
    <!--freemarker引入模板文件 使用相对路径来引入的-->
    <#include "../common/link.ftl" >
    <script>
        $(function () {
            //新增/编辑按钮点击事件
            $(".btn-input").click(function () {
                //清除模态框的数据
                 $("#editForm input").val('');
                var json = $(this).data("json");
                if(json){ //json有数据代表是编辑
                    $("#editForm input[name=id]").val(json.id);
                    $("#editForm input[name=title]").val(json.title);
                    $("#editForm input[name=intro]").val(json.intro);
                    $("#editForm input[name=sn]").val(json.sn);
                }
                //打开模态框
                $("#myModal").modal('show');
            })


            //保存
            $(".btn-submit").click(function () {
                //使用jquery-form插件来提交异步表单(有表单时会使用该插件,写的代码比较少)
                $("#editForm").ajaxSubmit(handlerMessage)
            })

        })
    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <!--页面头部-->
    <#include "../common/navbar.ftl" >
    <!--菜单回显 声明变量设置值-->
    <#assign currentMenu="systemDictionary"/>
    <!--菜单-->
    <#include "../common/menu.ftl" >
    <div class="content-wrapper">
        <section class="content-header">
            <h1>字典目录管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <!--高级查询--->
                <form class="form-inline" id="searchForm" action="/systemDictionary/list.do" method="post">
                    <input type="hidden" name="currentPage" id="currentPage" value="1">
                    <a href="#" class="btn btn-success btn-input" style="margin: 10px">
                        <span class="glyphicon glyphicon-plus"></span> 添加
                    </a>
                </form>
                <!--编写内容-->
                <div class="box-body table-responsive no-padding ">

                    <table class="table table-hover table-bordered">
                        <tr>
                            <th>编号</th>
                            <th>标题</th>
                            <th>编码</th>
                            <th>简介</th>
                            <th>操作</th>
                        </tr>
                            <#list result.list as systemDictionary>
                                  <tr>
                                      <!--freemarker 如果取值时是空值 会报错-->
                                      <td>${systemDictionary_index+1}</td>
                                      <td>${systemDictionary.title!}</td>
                                      <td>${systemDictionary.sn!}</td>
                                      <td>${systemDictionary.intro!}</td>
                                      <td>
                                          <!-- 使用data-*绑定自定义数据-->
                                          <a href="#"
                                             class="btn btn-info btn-xs btn-input"
                                             data-json='${systemDictionary.json}' >
                                              <span class="glyphicon glyphicon-pencil"></span> 编辑
                                          </a>
                                      </td>
                                  </tr>
                            </#list>
                    </table>
                    <!--分页-->
                    <#include "../common/page.ftl">


                </div>
            </div>
        </section>
    </div>
     <#include "../common/footer.ftl">
</div>


<!-- Modal模态框 -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="myModalLabel">新增/编辑</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/systemDictionary/saveOrUpdate.do" method="post" id="editForm">
                    <input type="hidden" name="id">
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="title" class="col-sm-3 control-label">目录标题：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="title" name="title"
                                   placeholder="请输入目录标题">
                        </div>
                    </div>
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="sn" class="col-sm-3 control-label">目录编码：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="sn" name="sn"
                                   placeholder="请输入目录编码">
                        </div>
                    </div>
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="intro" class="col-sm-3 control-label">目录简介：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="intro" name="intro"
                                   placeholder="请输入目录简介">
                        </div>
                    </div>
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
                <button type="button" class="btn btn-primary btn-submit">保存</button>
            </div>
        </div>
    </div>
</div>



</body>
</html>
