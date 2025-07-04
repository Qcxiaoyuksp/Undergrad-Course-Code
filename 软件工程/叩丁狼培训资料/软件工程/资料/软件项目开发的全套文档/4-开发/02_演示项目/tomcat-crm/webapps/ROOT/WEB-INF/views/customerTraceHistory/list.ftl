<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>跟进历史管理</title>
    <#include "../common/link.ftl">
    <script type="text/javascript">
        $(function () {
            $("#btn_query").click(function () {
                $("#currentPage").val(1);
                $("#searchForm").submit();
            });
        })
        //编辑
        $(function () {
            $(".inputBtn").click(function () {

                //弹出模态框
                $("#traceHistoryModal").modal("show");
                //数据复原
                $("#traceHistoryForm")[0].reset();

                //客户回显数据
                var data = $(this).data("json");
                if (data) {
                    $("#inputTitle").html("客户编辑");
                    $("#traceHistoryForm input[name='id']").val(data.id);
                    $("#traceHistoryForm input[name='customer.id']").val(data.customerId);
                    $("#traceHistoryForm input[name='customer.name']").val(data.customerName);
                    $("#traceHistoryForm input[name='traceTime']").val(data.traceTime);
                    $("#traceHistoryForm input[name='traceDetails']").val(data.traceDetails);
                    $("#traceHistoryForm select[name='traceResult']").val(data.traceResult);
                    $("#traceHistoryForm input[name='remark']").val(data.remark);
                    $("#traceHistoryForm select[name='type']").val(data.type);
                }
            })
        })

        //提交编辑表单
        $(function () {
            $(".traceHistorySubmit").click(function () {
                $("#traceHistoryForm").ajaxSubmit(function (data) {
                    if (data.success) {
                        window.location.reload();
                    } else {
                        $.messager.alert("温馨提示", data.msg)
                    }
                })
            })
        })
    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <#include "../common/navbar.ftl">
    <!--菜单回显-->
    <#assign currentMenu="customerTraceHistory">
    <#include "../common/menu.ftl">
    <div class="content-wrapper">
        <section class="content-header">
            <h1>跟进历史管理</h1>
        </section>
        <section class="content">
            <div class="box">
                <!--高级查询--->
                <div style="margin: 10px;">
                    <!--高级查询--->
                    <form class="form-inline" id="searchForm" action="/customerTraceHistory/list.do" method="post">
                        <input type="hidden" name="currentPage" id="currentPage" value="1">
                        <div class="form-group">
                            <label for="keyword">关键字:</label>
                            <input type="text" class="form-control" id="keyword" name="keyword" value="${(qo.keyword)!""}" placeholder="请输入姓名或电话">
                        </div>
                        <button id="btn_query" class="btn btn-primary"><span class="glyphicon glyphicon-search"></span>查询</button>
                    </form>
                </div>
                <table class="table table-striped table-hover">
                    <thead>
                    <tr>
                        <th>编号</th>
                        <th>姓名</th>
                        <th>跟进日期</th>
                        <th>跟进内容</th>
                        <th>跟进方式</th>
                        <th>跟进结果</th>
                        <th>录入人</th>
                    </tr>
                    </thead>
                    <#list result.list as entity>
                        <tr>
                            <td>${entity_index+1}</td>
                            <td>${entity.customer.name}</td>
                            <td>${entity.traceTime?string('yyyy-MM-dd')}</td>
                            <td>${entity.traceDetails!}</td>
                            <td>${entity.traceType.title!} </td>
                            <td>${entity.displayTraceResult!} </td>
                            <td>${entity.inputUser.name}</td>
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
