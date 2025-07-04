package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.ArrayList;
import java.util.List;

//预约服务接口
public interface IAppointmentService {
    //新增
    void save(Appointment appointment);

    //修改
    void update(Appointment appointment);

    //删除
    void delete(Long id);

    //根据id查询
    Appointment get(Long id);

    //查询全部
    List<Appointment> listAll();

    TablePageInfo<Appointment> query(AppointmentQuery qo);

    void cancel(Long id);

    void remove(Long[] ids);

    void arrival(Long id);
}
