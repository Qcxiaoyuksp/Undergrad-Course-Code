$(function () {


})

//每个页面的ajax的回调函数
var handlerMessage = function (data) { //form中已经设置了action,method
    if(data.success){ //用alert或者popup都可以
        $.messager.alert("温馨提示","保存成功!2s后自动关闭")
        window.setTimeout(function () {
            window.location.reload();
        },2000)
    }else{
        $.messager.popup(data.msg)
    }
}


$.messager.model = {
    ok:{text:"确认"},
    cancel:{text:"取消"}
}

//禁用数组添加[]的功能
jQuery.ajaxSettings.traditional = true;