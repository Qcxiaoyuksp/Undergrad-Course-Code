<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>移交历史管理</title>
    <#include "../common/link.ftl">
    <script>
        //编辑
        $(function () {
            $(".btn_input_modal").click(function () {
                //弹出模态框
                $("#editModal").modal("show");
                //修改模态框标题
                $(".modal-title").html("移交历史添加");
                //数据复原
                $("#editForm")[0].reset();

                //移交历史回显数据
                var data = $(this).data("json");
                if(data){
                    $(".modal-title").html("移交历史编辑");
                    $("input[name='id']").val(data.id);
                    $("input[name='name']").val(data.name);
                    $("input[name='sn']").val(data.sn);
                }
            })

        })


    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <#include "../common/navbar.ftl">
    <!--菜单回显-->
    <#assign currentMenu="customerTransfer">
    <#include "../common/menu.ftl">
    <div class="content-wrapper">
        <section class="content-header">
            <h1>移交历史管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <!--高级查询--->
                <div style="margin: 10px;">
                    <!--高级查询--->
                    <form class="form-inline" id="searchForm" action="/customerTransfer/list.do" method="post">
                        <input type="hidden" name="currentPage" id="currentPage" value="1">
                        <div class="form-group">
                            <label for="keyword">关键字:</label>
                            <input type="text" class="form-control" id="keyword" name="keyword" value="${(qo.keyword)!""}" placeholder="请输入姓名或电话">
                        </div>
                        <div class="form-group">
                        </div>
                        <button id="btn_query" class="btn btn-primary"><span class="glyphicon glyphicon-search"></span>查询</button>
                    </form>

                </div>
                <table class="table table-striped table-hover" >
                    <thead>
                    <tr>
                        <th>编号</th>
                        <th>客户姓名</th>
                        <th>操作日期</th>
                        <th>操作人</th>
                        <th>旧营销人员</th>
                        <th>新营销人员</th>
                        <th>移交原因</th>
                    </tr>
                    </thead>
               <#list result.list as entity>
                   <tr>
                       <td>${entity_index+1}</td>
                       <td>${entity.customer.name}</td>
                       <td>${entity.operateTime?string('yyyy-MM-dd HH:mm:ss')}</td>
                       <td>${entity.operator.name}</td>
                       <td>${entity.oldseller.name}</td>
                       <td>${entity.newseller.name}</td>
                       <td>${entity.reason!}</td>
                   </tr>
               </#list>
                </table>
            <#include "../common/page.ftl">
            </div>
        </section>
    </div>
    <#include "../common/footer.ftl">
</div>
</body>
</html>
