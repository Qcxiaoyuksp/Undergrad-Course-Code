package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.mapper.AppointmentMapper;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.business.service.IAppointmentService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.List;

@Service
@Transactional
public class AppointmentServiceImpl implements IAppointmentService {

    @Autowired
    private AppointmentMapper appointmentMapper;


    @Override
    public TablePageInfo<Appointment> query(AppointmentQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());
        if(qo.getStatus() == null){
            return new TablePageInfo<Appointment>(appointmentMapper.selectForListAndNotDelete(qo));
        }
        return new TablePageInfo<Appointment>(appointmentMapper.selectForList(qo));
    }


    @Override
    public void save(Appointment appointment) {
        // 从安全角度考虑，前台传递过来的对象是不可以直接使用的。
        // 所以我们都新建对象。这样无论如何都不会因为前台传递了默认值而改变我们的默认值数据。
        Appointment obj = new Appointment();
        obj.setCustomerName(appointment.getCustomerName());
        obj.setCustomerPhone(appointment.getCustomerPhone());
        obj.setAppointmentTime(appointment.getAppointmentTime());
        obj.setLicensePlate(appointment.getLicensePlate());
        obj.setCarSeries(appointment.getCarSeries());
        obj.setServiceType(appointment.getServiceType());
        obj.setCreateTime(new Date());
        obj.setInfo(appointment.getInfo());
        appointmentMapper.insert(obj);
    }

    @Override
    public Appointment get(Long id) {
        return appointmentMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(Appointment appointment) {
        Appointment obj = this.get(appointment.getId());
        // 只有状态为预约中才可以点击编辑按钮。其他都不可以。
        if (!Appointment.STATUS_APPOINTMENT.equals(obj.getStatus())) {
            throw new BusinessException("非预约中的记录不能进行修改");
        }
        obj.setCustomerName(appointment.getCustomerName());
        obj.setCustomerPhone(appointment.getCustomerPhone());
        obj.setAppointmentTime(appointment.getAppointmentTime());
        obj.setLicensePlate(appointment.getLicensePlate());
        obj.setCarSeries(appointment.getCarSeries());
        obj.setServiceType(appointment.getServiceType());
        obj.setInfo(appointment.getInfo());
        appointmentMapper.updateByPrimaryKey(obj);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            appointmentMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public List<Appointment> list() {
        return appointmentMapper.selectAll();
    }

    @Override
    public void arrival(Long id) {
        Appointment appointment = this.get(id);
        if(!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
            throw new BusinessException("只有预约中的记录才可以进行到店操作");
        }
        appointmentMapper.arrival(id,Appointment.STATUS_ARRIVAL,new Date());
    }

    @Override
    public void cancel(Long id) {
        Appointment appointment = this.get(id);
        if(!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
            throw new BusinessException("只有预约中的记录才可以进行取消操作");
        }
        appointmentMapper.changeStatus(id,Appointment.STATUS_CANCEL);
    }

    @Override
    public void remove(Long[] ids) {
        if(ids != null && ids.length > 0){
            for (Long id : ids) {
                Appointment appointment = this.get(id);
                if(!Appointment.STATUS_APPOINTMENT.equals(appointment.getStatus())){
                    throw new BusinessException("只有预约中的记录才可以进行删除操作");
                }
                appointmentMapper.changeStatus(id,Appointment.STATUS_DELETE);
            }
        }
    }

    @Override
    public void changeStatus(Long appointmentId, Integer statusPaid) {
        appointmentMapper.changeStatus(appointmentId,statusPaid);
    }
}
