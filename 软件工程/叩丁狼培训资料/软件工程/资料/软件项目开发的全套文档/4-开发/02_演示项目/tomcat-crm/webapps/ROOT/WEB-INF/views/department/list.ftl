<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>部门管理</title>
    <!--freemarker引入模板文件 使用相对路径来引入的-->
    <#include "../common/link.ftl" >
    <script>
        $(function () {
            //新增/编辑按钮点击事件
            $(".btn-input").click(function () {
                //清除模态框的数据
                 $("#editForm input").val('');
                //$("#editForm")[0].reset(); //不能清除隐藏域
                //获取事件源绑定的数据 使用data方法可以很方便获取data-*开头的属性的数据
                var json = $(this).data("json");
                if(json){ //json有数据代表是编辑
                    $("#editForm input[name=id]").val(json.id);
                    $("#editForm input[name=name]").val(json.name);
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
               //提交异步请求
                /*$.post('/department/saveOrUpdate.do',$("#editForm").serialize(),function (data) {
                    if(data.success){ //用alert或者popup都可以
                       $.messager.alert("温馨提示","保存成功!2s后自动关闭")
                       window.setTimeout(function () {
                           window.location.reload();
                       },2000)
                    }else{
                       $.messager.popup(data.msg)
                    }
                })*/

           //删除按钮
           $(".btn-delete").click(function () {
                //获取当前点击的部门id
               var id = $(this).data('id');
               //提示确认框
               $.messager.confirm("警告","是否确认删除?",function () {
                   //发送ajax请求
                   $.get('/department/delete.do',{id:id},handlerMessage)
               })


           })



        })
    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <!--页面头部-->
    <#include "../common/navbar.ftl" >
    <!--菜单回显 声明变量设置值-->
    <#assign currentMenu="department"/>
    <!--菜单-->
    <#include "../common/menu.ftl" >
    <div class="content-wrapper">
        <section class="content-header">
            <h1>部门管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <!--高级查询--->
                <form class="form-inline" id="searchForm" action="/department/list.do" method="post">
                    <input type="hidden" name="currentPage" id="currentPage" value="1">
                    <@shiro.hasPermission name="department:saveOrUpdate">
                        <a href="#" class="btn btn-success btn-input" style="margin: 10px">
                            <span class="glyphicon glyphicon-plus"></span> 添加
                        </a>
                    </@shiro.hasPermission>
                </form>
                <!--编写内容-->
                <div class="box-body table-responsive no-padding ">

                    <table class="table table-hover table-bordered">
                        <tr>
                            <th>编号</th>
                            <th>部门名称</th>
                            <th>部门编号</th>
                            <th>操作</th>
                        </tr>
                            <#list result.list as department>
                                  <tr>
                                      <!--freemarker 如果取值时是空值 会报错-->
                                      <td>${department_index+1}</td>
                                      <td>${department.name!}</td>
                                      <td>${department.sn!}</td>
                                      <td>
                                          <!-- 使用data-*绑定自定义数据-->
                                          <a href="#"
                                             class="btn btn-info btn-xs btn-input"
                                             data-json='${department.json}' >
                                              <span class="glyphicon glyphicon-pencil"></span> 编辑
                                          </a>
                                          <@shiro.hasPermission name="department:delete">
                                              <a href="#"
                                                 class="btn btn-danger btn-xs btn-delete"
                                                    data-id='${department.id}'>
                                                  <span class="glyphicon glyphicon-trash"></span> 删除
                                              </a>
                                          </@shiro.hasPermission>
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
                <form class="form-horizontal" action="/department/saveOrUpdate.do" method="post" id="editForm">
                    <input type="hidden" name="id">
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="name" class="col-sm-3 control-label">名称：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="name" name="name"
                                   placeholder="请输入部门名">
                        </div>
                    </div>
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="sn" class="col-sm-3 control-label">编码：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="sn" name="sn"
                                   placeholder="请输入部门编码">
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
