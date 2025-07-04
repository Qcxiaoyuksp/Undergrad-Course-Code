<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>潜在客户管理</title>
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
                    $("#editForm input[name=name]").val(json.name);
                    $("#editForm input[name=age]").val(json.age);
                    $("#editForm input[name=qq]").val(json.qq);
                    $("#editForm select[name=gender]").val(json.gender);
                    $("#editForm input[name=tel]").val(json.tel);
                    $("#editForm select[name='job.id']").val(json.jobId);
                    $("#editForm select[name='source.id']").val(json.sourceId);
                }
                //打开模态框
                $("#editModal").modal('show');
            })


            //保存
            $(".btn-submit").click(function () {
                //使用jquery-form插件来提交异步表单(有表单时会使用该插件,写的代码比较少)
                $("#editForm").ajaxSubmit(handlerMessage)
            })
            //-----------------------------------
            //跟进按钮
            $(".btn-trace").click(function () {
                var json = $(this).data('json'); //json是客户对象
                $("#traceForm input[name=name]").val(json.name)
                $("#traceForm input[name='customer.id']").val(json.id);//把客户id设置到跟进历史对象的客户id中
                $("#traceModal").modal('show');
            })
            
            //跟进保存按钮
            $(".traceSubmit").click(function () {
                $("#traceForm").ajaxSubmit(handlerMessage)
            })

            //跟进时间使用日期插件
            $("input[name=traceTime]").datepicker({
                language: "zh-CN",
                autoclose: true,
                todayHighlight: true
            });
            //-----------------------------------------------
            //移交按钮
            $(".btn-transfer").click(function () {
                var json = $(this).data('json'); //json是客户对象
                $("#transferForm input[name='customer.name']").val(json.name);
                $("#transferForm input[name='customer.id']").val(json.id);
                $("#transferForm input[name='oldseller.name']").val(json.sellerName);
                $("#transferForm input[name='oldseller.id']").val(json.sellerId);

                $("#transferModal").modal('show');
            })

            //跟进保存按钮
            $(".transferSubmit").click(function () {
                $("#transferForm").ajaxSubmit(handlerMessage)
            })
            //-------------------------------------
            $(".statusBtn").click(function () {

                //弹出模态框
                $("#statusModal").modal("show");
                //数据复原
                $("#statusForm")[0].reset();

                //客户回显数据
                var data = $(this).data("json");
                if(data){
                    $("#statusForm input[name='customerId']").val(data.id);
                    $("#statusForm input[name='name']").val(data.name);
                }
            })


            $(".statusSubmit").click(function () {
                $("#statusForm").ajaxSubmit(function (data) {
                    if(data.success){
                        window.location.reload();
                    }else{
                        $.messager.alert("温馨提示", data.msg)
                    }
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
    <#assign currentMenu="customer_potential"/>
    <!--菜单-->
    <#include "../common/menu.ftl" >
    <div class="content-wrapper">
        <section class="content-header">
            <h1>潜在客户管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <!--高级查询--->
                <form class="form-inline" id="searchForm" action="/customer/potentialList.do" method="post">
                    <input type="hidden" name="currentPage" id="currentPage" value="1">

                    <div class="form-group">
                        <label for="keyword">关键字:</label>
                        <input type="text" class="form-control" id="keyword" name="keyword"
                               value="${qo.keyword!}" placeholder="请输入姓名/电话">
                    </div>
                    <!--管理员和经理才能看到该下拉框-->
                    <@shiro.hasAnyRoles name="admin,Market_Manager">
                        <div class="form-group">
                            <label for="dept"> 销售人员:</label>
                            <select class="form-control" id="sellerId" name="sellerId">
                                <option value="-1">全部</option>
                                <#list employees as e>
                                    <option value="${e.id}">${e.name}</option>
                                </#list>
                            </select>
                            <script>
                                $("#sellerId").val(${qo.sellerId})
                            </script>
                        </div>
                    </@shiro.hasAnyRoles>
                    <button id="btn_query" class="btn btn-primary"><span class="glyphicon glyphicon-search"></span> 查询</button>

                    <a href="#" class="btn btn-success btn-input" style="margin: 10px">
                        <span class="glyphicon glyphicon-plus"></span> 添加
                    </a>
                </form>
                <!--编写内容-->
                <div class="box-body table-responsive no-padding ">

                    <table class="table table-hover table-bordered">
                        <tr>
                            <th>编号</th>
                            <th>姓名</th>
                            <th>电话</th>
                            <th>QQ</th>
                            <th>职业</th>
                            <th>来源</th>
                            <th>销售员</th>
                            <th>状态</th>
                            <th>录入时间</th>
                            <th>操作</th>
                        </tr>
                            <#list result.list as customer>
                                  <tr>
                                      <!--freemarker 如果取值时是空值 会报错-->
                                      <td>${customer_index+1}</td>
                                      <td>${customer.name!}</td>
                                      <td>${customer.tel!}</td>
                                      <td>${customer.qq!}</td>
                                      <td>${(customer.job.title)!}</td>
                                      <td>${(customer.source.title)!}</td>
                                      <td>${(customer.seller.name)!}</td>
                                      <td>${customer.statusName!}</td>
                                      <td>${(customer.inputTime?string('yyyy-MM-dd'))!}</td>
                                      <td>
                                          <!-- 使用data-*绑定自定义数据-->
                                         <a href="#"
                                             class="btn btn-info btn-xs btn-input"
                                             data-json='${customer.json}' >
                                              <span class="glyphicon glyphicon-pencil"></span> 编辑
                                          </a>
    
                                          <a href="#"
                                             class="btn btn-success btn-xs btn-trace"
                                             data-json='${customer.json}' >
                                              <span class="glyphicon glyphicon-phone"></span> 跟进
                                          </a>
                                <!--管理员和经理才能看到该下拉框-->
                                <@shiro.hasAnyRoles name="admin,Market_Manager">
                                          <a href="#"
                                             class="btn btn-danger btn-xs btn-transfer"
                                             data-json='${customer.json}' >
                                              <span class="glyphicon glyphicon-phone"></span> 移交
                                          </a>
                                </@shiro.hasAnyRoles>
                                          <a class="btn btn-danger btn-xs statusBtn"  data-json='${customer.json}'>
                                              <span class="glyphicon glyphicon-pencil"></span>修改状态
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
<div class="modal fade" id="editModal">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title inputTitle">客户编辑</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/customer/saveOrUpdate.do" method="post" id="editForm">
                    <input type="hidden" value="" name="id">
                    <div class="form-group" >
                        <label  class="col-sm-3 control-label">客户名称：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" name="name"
                                   placeholder="请输入客户姓名"/>
                        </div>
                    </div>
                    <div class="form-group">
                        <label  class="col-sm-3 control-label">客户年龄：</label>
                        <div class="col-sm-6">
                            <input type="number" class="form-control" name="age"
                                   placeholder="请输入客户年龄"/>
                        </div>
                    </div>
                    <div class="form-group" >
                        <label  class="col-sm-3 control-label">客户性别：</label>
                        <div class="col-sm-6">
                            <select class="form-control" name="gender">
                                <option value="1">男</option>
                                <option value="0">女</option>
                            </select>
                        </div>
                    </div>
                    <div class="form-group">
                        <label  class="col-sm-3 control-label">客户电话：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" name="tel"
                                   placeholder="请输入客户电话"/>
                        </div>
                    </div>
                    <div class="form-group" >
                        <label  class="col-sm-3 control-label">客户QQ：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" name="qq"
                                   placeholder="请输入客户QQ"/>
                        </div>
                    </div>
                    <div class="form-group">
                        <label  class="col-sm-3 control-label">客户工作：</label>
                        <div class="col-sm-6">
                            <select class="form-control" name="job.id">
                                <#list jobs as j>
                                    <option value="${j.id}">${j.title}</option>
                                </#list>
                            </select>
                        </div>
                    </div>
                    <div class="form-group">
                        <label  class="col-sm-3 control-label">客户来源：</label>
                        <div class="col-sm-6">
                            <select class="form-control" name="source.id">
                               <#list sources as s>
                                    <option value="${s.id}">${s.title}</option>
                                </#list>
                            </select>
                        </div>
                    </div>
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-primary btn-submit" >保存</button>
                <button type="button" class="btn btn-default" data-dismiss="modal" >取消</button>
            </div>
        </div>
    </div>
</div>

<#--跟进历史-->
<div class="modal fade" id="traceModal" tabindex="-1" role="dialog" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                <h4 class="modal-title">跟进</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/customerTraceHistory/saveOrUpdate.do" method="post" id="traceForm">
                <#--新增,新增跟进历史没有ID,客户应该要有ID,不然就不知道当前是哪个客户的跟进历史-->
                    <input type="hidden" name="customer.id"/>
                    <div class="form-group" >
                        <label class="col-lg-4 control-label">客户姓名：</label>
                        <div class="col-lg-6">
                            <input type="text" class="form-control" readonly name="name"/>
                        </div>
                    </div>
                    <div class="form-group" >
                        <label class="col-lg-4 control-label">跟进时间：</label>
                        <div class="col-lg-6 ">
                            <input type="text" class="form-control"  name="traceTime"  placeholder="请输入跟进时间">
                        </div>
                    </div>

                    <div class="form-group">
                        <label class="col-lg-4 control-label">交流方式：</label>
                        <div class="col-lg-6">
                            <select class="form-control" name="traceType.id">
                                <#list ccts as c>
                                    <option value="${c.id}">${c.title}</option>
                                </#list>
                            </select>
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-lg-4 control-label">跟进结果：</label>
                        <div class="col-lg-6">
                            <select class="form-control" name="traceResult">
                                <option value="3">优</option>
                                <option value="2">中</option>
                                <option value="1">差</option>
                            </select>
                        </div>
                    </div>
                    <div class="form-group" >
                        <label class="col-lg-4 control-label">跟进记录：</label>
                        <div class="col-lg-6">
                            <textarea type="text" class="form-control" name="traceDetails"
                                      placeholder="请输入跟进记录" name="remark"></textarea>
                        </div>
                    </div>
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-primary traceSubmit">保存</button>
                <button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
            </div>
        </div>
    </div>
</div>


<#--移交模态框-->
<div id="transferModal" class="modal fade" tabindex="-1" role="dialog">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title">新增/编辑</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/customerTransfer/saveOrUpdate.do" method="post" id="transferForm" style="margin: -3px 118px">
                    <input type="hidden" name="id" id="customerTransferId"/>
                    <div class="form-group" >
                        <label for="name" class="col-sm-4 control-label">客户姓名：</label>
                        <div class="col-sm-8">
                            <input type="text" class="form-control"  name="customer.name"   readonly >
                            <input type="hidden" class="form-control"  name="customer.id"  >
                        </div>
                    </div>

                    <div class="form-group">
                        <label for="sn" class="col-sm-4 control-label">旧营销人员：</label>
                        <div class="col-sm-8">
                            <input type="text" class="form-control"  name="oldseller.name" readonly >
                            <input type="hidden" class="form-control"    name="oldseller.id"  >
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="sn" class="col-sm-4 control-label">新营销人员：</label>
                        <div class="col-sm-8">
                            <select name="newseller.id" id="newseller" class="form-control">
                                <#list employees as e>
                                    <option value="${e.id}">${e.name}</option>
                                </#list>
                            </select>
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="sn" class="col-sm-4 control-label">移交原因：</label>
                        <div class="col-sm-8">
                            <textarea type="text" class="form-control" id="reason" name="reason" cols="10" ></textarea>
                        </div>
                    </div>

                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-primary transferSubmit" >保存</button>
            </div>
        </div><!-- /.modal-content -->
    </div><!-- /.modal-dialog -->
</div><!-- /.modal -->

<#--修改状态-->
<div class="modal fade" id="statusModal" tabindex="-1" role="dialog" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                <h4 class="modal-title">修改客户状态</h4>
            </div>
            <div class="modal-body">
                <form class="form-horizontal" action="/customer/updateStatus.do" method="post" id="statusForm">
                    <input type="hidden" name="customerId"/>
                    <div class="form-group" >
                        <label class="col-lg-4 control-label">客户名称：</label>
                        <div class="col-lg-6">
                            <input type="text" class="form-control" name="name"
                                   readonly placeholder="请输入客户名称"/>
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-lg-4 control-label">客户状态：</label>
                        <div class="col-lg-6">
                            <select class="form-control" name="status">
                                <option value="0">潜在客户</option>
                                <option value="2">开发失败</option>
                                <option value="4">移入客户池</option>
                            </select>
                        </div>
                    </div>
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
                <button type="button" class="btn btn-primary statusSubmit">保存</button>
            </div>
        </div>
    </div>
</div>
</body>
</html>
