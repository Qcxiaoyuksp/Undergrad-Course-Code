<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>字典明细管理</title>
    <!--freemarker引入模板文件 使用相对路径来引入的-->
    <#include "../common/link.ftl" >
    <script>
        $(function () {
            //新增/编辑按钮点击事件
            $(".btn-input").click(function () {
                //清除模态框的数据
                $("#editForm input").val('');
                var json = $(this).data("json");
                //把目录的名称设置到模态框的目录名称input中
                $("#parentName").val($("a[data-id=${qo.parentId}]").text());
                $("#parentId").val(${qo.parentId});

                if (json) { //json有数据代表是编辑
                    $("#editForm input[name=id]").val(json.id);
                    $("#editForm input[name=title]").val(json.title);
                    $("#editForm input[name=sequence]").val(json.sequence);
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
    <#assign currentMenu="systemDictionaryItem"/>
    <!--菜单-->
    <#include "../common/menu.ftl" >
    <div class="content-wrapper">
        <section class="content-header">
            <h1>字典明细管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <div class="row" style="margin:20px">
                    <div class="col-xs-3">
                        <div class="panel panel-default">
                            <div class="panel-heading">字典目录</div>
                            <div class="panel-body">
                                <div class="list-group">
                                    <#list systemDictionarys as dic>
                                        <a data-id="${dic.id}" href="/systemDictionaryItem/list.do?parentId=${dic.id}" class="list-group-item">${dic.title!}</a>
                                    </#list>
                                    <script>
                                        $("a[data-id=${qo.parentId}]").addClass('active');
                                    </script>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="col-xs-9">
                        <!--高级查询--->
                        <form class="form-inline" id="searchForm" action="/systemDictionaryItem/list.do" method="post">
                            <input type="hidden" name="currentPage" id="currentPage" value="1">
                            <!--带上qo的parentId到后台,解决parentId丢失问题-->
                            <input type="hidden" name="parentId"  value="${qo.parentId}">
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
                                    <th>序号</th>
                                    <th>操作</th>
                                </tr>
                            <#list result.list as systemDictionaryItem>
                                  <tr>
                                      <!--freemarker 如果取值时是空值 会报错-->
                                      <td>${systemDictionaryItem_index+1}</td>
                                      <td>${systemDictionaryItem.title!}</td>
                                      <td>${systemDictionaryItem.sequence!}</td>
                                      <td>
                                          <!-- 使用data-*绑定自定义数据-->
                                        <a href="#"
                                           class="btn btn-info btn-xs btn-input"
                                           data-json='${systemDictionaryItem.json}' >
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
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span>
                </button>
                <h4 class="modal-title" id="myModalLabel">新增/编辑</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/systemDictionaryItem/saveOrUpdate.do" method="post"
                      id="editForm">
                    <input type="hidden" name="id">
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="intro" class="col-sm-3 control-label">字典目录：</label>
                        <div class="col-sm-6">
                            <!-- 用来给用户看的 -->
                            <input type="text" class="form-control" id="parentName" name="parentName" readonly>
                            <!-- 用来提交到后台关联的 -->
                            <input type="hidden" id="parentId" name="parentId">
                        </div>
                    </div>
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="title" class="col-sm-3 control-label">明细标题：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="title" name="title"
                                   placeholder="请输入明细标题">
                        </div>
                    </div>
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="sn" class="col-sm-3 control-label">明细序号：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="sequence" name="sequence"
                                   placeholder="请输入明细编码">
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
