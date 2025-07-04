<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>潜在客户报表查询</title>
    <!--freemarker引入模板文件 使用相对路径来引入的-->
    <#include "../common/link.ftl" >
    <script>
        $(function () {
            $('.input-daterange').datepicker({
                language: "zh-CN",
                autoclose: true,
                todayHighlight: true,
                clearBtn: true
            });

            $(".btn-chart").click(function () {
                //清空模态框的缓存
                $('#myModal').removeData('bs.modal');
                //告诉模态框图形报表url是哪个,加载内容并且放到模态框
                var url = $(this).data('url');
                $('#myModal').modal({ //加上高级查询的条件
                    remote : url + "?" + $("#searchForm").serialize()
                })
                $("#myModal").modal('show');
            })
        })
    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <!--页面头部-->
    <#include "../common/navbar.ftl" >
    <!--菜单回显 声明变量设置值-->
    <#assign currentMenu="customerReport"/>
    <!--菜单-->
    <#include "../common/menu.ftl" >
    <div class="content-wrapper">
        <section class="content-header">
            <h1>潜在客户报表查询</h1>
        </section>
        <section class="content">
            <div class="box">
                <div style="margin: 10px;">
                <!--高级查询--->
                <form class="form-inline" id="searchForm" action="/customerReport/list.do" method="post">
                    <input type="hidden" name="currentPage" id="currentPage" value="1">
                    <div class="form-group">
                        <label for="keyword">员工姓名:</label>
                        <input type="text" class="form-control" id="keyword" name="keyword" value="${qo.keyword!}">
                    </div>
                    <div class="form-group">
                        <label>时间段查询:</label>
                        <div class="input-daterange input-group" id="datepicker">
                            <input type="text" class="input-sm form-control" name="beginDate"
                                   value="${(qo.beginDate?string('yyyy-MM-dd'))!}" />
                            <span class="input-group-addon">to</span>
                            <input type="text" class="input-sm form-control" name="endDate"
                                   value="${(qo.endDate?string('yyyy-MM-dd'))!}" />
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="status">分组类型:</label>
                        <select class="form-control" id="groupType" name="groupType">
                            <option value="e.name">员工</option>
                            <option value="DATE_FORMAT(c.input_time, '%Y')">
                                年
                            </option>
                            <option value="DATE_FORMAT(c.input_time, '%Y-%m')">
                                月
                            </option>
                            <option value="DATE_FORMAT(c.input_time, '%Y-%m-%d')">
                                日
                            </option>
                        </select>
                        <script>
                            $("#groupType").val("${qo.groupType!}")
                        </script>
                    </div>

                    <button id="btn_query" class="btn btn-primary"><span class="glyphicon glyphicon-search"></span> 查询</button>
                    <button type="button" class="btn btn-info btn-chart" data-url="/customerReport/listByBar.do">
                        <span class="glyphicon glyphicon-stats"></span> 柱状图
                    </button>
                    <button type="button" class="btn btn-warning btn-chart"  data-url="/customerReport/listByPie.do">
                        <span class="glyphicon glyphicon-dashboard"></span> 饼状图
                    </button>

                </form>
                </div>
                <!--编写内容-->
                <div class="box-body table-responsive no-padding ">

                    <table class="table table-hover table-bordered">
                        <tr>
                            <th>分组类型</th>
                            <th>潜在客户新增数</th>
                        </tr>
                            <#list result.list as map>
                                  <tr>
                                      <!--freemarker 如果取值时是空值 会报错-->
                                      <td>${map.groupType!}</td>
                                      <td>${map.number!}</td>
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
        </div>
    </div>
</div>



</body>
</html>
