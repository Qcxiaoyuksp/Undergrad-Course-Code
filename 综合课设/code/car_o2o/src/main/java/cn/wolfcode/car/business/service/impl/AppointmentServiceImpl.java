package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.mapper.AppointmentMapper;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.business.service.IAppointmentService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Service
public class AppointmentServiceImpl implements IAppointmentService {

    @Autowired
    private AppointmentMapper appointmentMapper;

    @Override
    public void save(Appointment appointment) {
        //添加创建时间
        appointment.setCreateTime(new Date());
        appointmentMapper.insert(appointment);
    }

    @Override
    public void update(Appointment appointment) {
        //只有预约中才能修改
        if (!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
            throw new BusinessException("只有预约中的服务才可以修改");
        }
        appointmentMapper.updateByPrimaryKey(appointment);
    }

    @Override
    public void delete(Long id) {
        appointmentMapper.deleteByPrimaryKey(id);
    }

    @Override
    public Appointment get(Long id) {
        return appointmentMapper.selectByPrimaryKey(id);
    }

    //到店时间插入
    @Override
    @Transactional
    public void arrival(Long id) {
        Appointment appointment = this.get(id);
        //只有预约中才能修改
        if (!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
            throw new BusinessException("只有预约中才可以到店");
        }

        //将状态修改为到店
        appointmentMapper.changeStatusById(Appointment.STATUS_ARRIVAL,id);
        //插入到店时间
        appointmentMapper.changeArrivalTime(id,new Date());
    }

    //批量删除remove
    @Override
    public void remove(Long[] ids) {
        if (ids != null || ids.length > 0){
            for (Long id : ids) {
                Appointment appointment = this.get(id);
                //只有预约中才能修改
                if (Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
                    appointmentMapper.deleteByPrimaryKey(id);
                }
            }
        }
    }

    //取消逻辑
    @Override
    public void cancel(Long id) {
        Appointment appointment = this.get(id);
        //只有预约中才能修改
        if (!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
            throw new BusinessException("只有预约中的服务才可以取消");
        }
        //将用户状态从预约中修改为取消
        appointmentMapper.changeStatusById(Appointment.STATUS_CANCEL,id);
    }

    //分页查询方法
    @Override
    public TablePageInfo<Appointment> query(AppointmentQuery qo) {
        //分页框架要第几页和要多少数据
        PageHelper.startPage(qo.getPageNum(),qo.getPageSize());
        List<Appointment> list = appointmentMapper.selectForList(qo);
        TablePageInfo<Appointment> tablePageInfo = new TablePageInfo<>(list);
        return tablePageInfo;
    }

    @Override
    public List<Appointment> listAll() {
       return appointmentMapper.selectAll();
    }
}
