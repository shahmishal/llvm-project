//===-- sanitizer_platform_limits_netbsd.cc -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is a part of Sanitizer common code.
//
// Sizes and layouts of platform-specific NetBSD data structures.
//===----------------------------------------------------------------------===//

#include "sanitizer_platform.h"

#if SANITIZER_NETBSD
#include <sys/param.h>
#include <sys/types.h>

#include <altq/altq.h>
#include <altq/altq_afmap.h>
#include <altq/altq_blue.h>
#include <altq/altq_cbq.h>
#include <altq/altq_cdnr.h>
#include <altq/altq_fifoq.h>
#include <altq/altq_hfsc.h>
#include <altq/altq_jobs.h>
#include <altq/altq_priq.h>
#include <altq/altq_red.h>
#include <altq/altq_rio.h>
#include <altq/altq_wfq.h>
#include <arpa/inet.h>
#include <crypto/cryptodev.h>
#include <dev/apm/apmio.h>
#include <dev/dm/netbsd-dm.h>
#include <dev/dmover/dmover_io.h>
#include <dev/dtv/dtvio_demux.h>
#include <dev/dtv/dtvio_frontend.h>
#include <dev/filemon/filemon.h>
#include <dev/hdaudio/hdaudioio.h>
#include <dev/hdmicec/hdmicecio.h>
#include <dev/hpc/hpcfbio.h>
#include <dev/i2o/iopio.h>
#include <dev/ic/athioctl.h>
#include <dev/ic/bt8xx.h>
#include <dev/ic/icp_ioctl.h>
#include <dev/ic/isp_ioctl.h>
#include <dev/ic/mlxio.h>
#include <dev/ic/nvmeio.h>
#include <dev/ir/irdaio.h>
#include <dev/isa/isvio.h>
#include <dev/isa/satlinkio.h>
#include <dev/isa/wtreg.h>
#include <dev/iscsi/iscsi_ioctl.h>
#include <dev/ofw/openfirmio.h>
#include <dev/pci/amrio.h>

#include <dev/pci/mlyreg.h>
#include <dev/pci/mlyio.h>

#include <dev/pci/pciio.h>
#include <dev/pci/tweio.h>
#include <dev/pcmcia/if_cnwioctl.h>
#include <dirent.h>
#include <glob.h>
#include <grp.h>
#include <ifaddrs.h>
#include <limits.h>
#include <link_elf.h>
#include <net/if.h>
#include <net/if_ether.h>
#include <net/ppp_defs.h>
#include <net/route.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_compat.h>
#include <netinet/ip_fil.h>
#include <netinet/ip_mroute.h>
#include <poll.h>
#include <pthread.h>
#include <pwd.h>
#include <semaphore.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/disk.h>
#include <sys/disklabel.h>
#include <sys/mount.h>
#define RAY_DO_SIGLEV
#include <dev/biovar.h>
#include <dev/bluetooth/btdev.h>
#include <dev/bluetooth/btsco.h>
#include <dev/ccdvar.h>
#include <dev/cgdvar.h>
#include <dev/fssvar.h>
#include <dev/kttcpio.h>
#include <dev/lockstat.h>
#include <dev/md.h>
#include <dev/pcmcia/if_rayreg.h>
#include <dev/raidframe/raidframeio.h>
#include <dev/sbus/mbppio.h>
#include <dev/scsipi/ses.h>
#include <dev/spkrio.h>
#include <dev/sun/disklabel.h>
#include <dev/sun/fbio.h>
#include <dev/sun/kbio.h>
#include <dev/sun/vuid_event.h>
#include <dev/tc/sticio.h>
#include <dev/usb/ukyopon.h>
#include <dev/usb/urio.h>
#include <dev/usb/usb.h>
#include <dev/usb/utoppy.h>
#include <dev/vme/xio.h>
#include <dev/vndvar.h>
#include <dev/wscons/wsconsio.h>
#include <dev/wscons/wsdisplay_usl_io.h>
#include <net/bpf.h>
#include <net/if_atm.h>
#include <net/if_gre.h>
#include <net/if_ppp.h>
#include <net/if_pppoe.h>
#include <net/if_sppp.h>
#include <net/if_srt.h>
#include <net/if_tap.h>
#include <net/if_tun.h>
#include <net/npf.h>
#include <net/pfvar.h>
#include <net/slip.h>
#include <netbt/hci.h>
#include <netinet/ip_nat.h>
#include <netinet/ip_proxy.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netnatm/natm.h>
#include <netsmb/smb_dev.h>
#include <soundcard.h>
#include <sys/agpio.h>
#include <sys/ataio.h>
#include <sys/audioio.h>
#include <sys/cdio.h>
#include <sys/chio.h>
#include <sys/clockctl.h>
#include <sys/cpuio.h>
#include <sys/dkio.h>
#include <sys/drvctlio.h>
#include <sys/dvdio.h>
#include <sys/envsys.h>
#include <sys/event.h>
#include <sys/fdio.h>
#include <sys/filio.h>
#include <sys/gpio.h>
#include <sys/ioctl.h>
#include <sys/ioctl_compat.h>
#include <sys/joystick.h>
#include <sys/ksyms.h>
#include <sys/lua.h>
#include <sys/midiio.h>
#include <sys/mtio.h>
#include <sys/power.h>
#include <sys/radioio.h>
#include <sys/rndio.h>
#include <sys/scanio.h>
#include <sys/scsiio.h>
#include <sys/sockio.h>
#include <sys/timepps.h>
#include <sys/ttycom.h>
#include <sys/verified_exec.h>
#include <sys/videoio.h>
#include <sys/wdog.h>
//#include <xen/xenio.h>
#include <sys/event.h>
#include <sys/filio.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/mqueue.h>
#include <sys/msg.h>
#include <sys/mtio.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/timespec.h>
#include <sys/timex.h>
#include <sys/types.h>
#include <sys/ucontext.h>
#include <sys/utsname.h>
#include <term.h>
#include <termios.h>
#include <time.h>
#include <ttyent.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#include <wchar.h>
#include <wordexp.h>

// Include these after system headers to avoid name clashes and ambiguities.
#include "sanitizer_internal_defs.h"
#include "sanitizer_platform_limits_netbsd.h"

namespace __sanitizer {
unsigned struct_utsname_sz = sizeof(struct utsname);
unsigned struct_stat_sz = sizeof(struct stat);
unsigned struct_rusage_sz = sizeof(struct rusage);
unsigned struct_tm_sz = sizeof(struct tm);
unsigned struct_passwd_sz = sizeof(struct passwd);
unsigned struct_group_sz = sizeof(struct group);
unsigned siginfo_t_sz = sizeof(siginfo_t);
unsigned struct_sigaction_sz = sizeof(struct sigaction);
unsigned struct_itimerval_sz = sizeof(struct itimerval);
unsigned pthread_t_sz = sizeof(pthread_t);
unsigned pthread_mutex_t_sz = sizeof(pthread_mutex_t);
unsigned pthread_cond_t_sz = sizeof(pthread_cond_t);
unsigned pid_t_sz = sizeof(pid_t);
unsigned timeval_sz = sizeof(timeval);
unsigned uid_t_sz = sizeof(uid_t);
unsigned gid_t_sz = sizeof(gid_t);
unsigned mbstate_t_sz = sizeof(mbstate_t);
unsigned sigset_t_sz = sizeof(sigset_t);
unsigned struct_timezone_sz = sizeof(struct timezone);
unsigned struct_tms_sz = sizeof(struct tms);
unsigned struct_sigevent_sz = sizeof(struct sigevent);
unsigned struct_sched_param_sz = sizeof(struct sched_param);
unsigned struct_sockaddr_sz = sizeof(struct sockaddr);
unsigned ucontext_t_sz = sizeof(ucontext_t);
unsigned struct_rlimit_sz = sizeof(struct rlimit);
unsigned struct_timespec_sz = sizeof(struct timespec);
unsigned struct_sembuf_sz = sizeof(struct sembuf);
unsigned struct_kevent_sz = sizeof(struct kevent);
unsigned struct_utimbuf_sz = sizeof(struct utimbuf);
unsigned struct_itimerspec_sz = sizeof(struct itimerspec);
unsigned struct_timex_sz = sizeof(struct timex);
unsigned struct_msqid_ds_sz = sizeof(struct msqid_ds);
unsigned struct_mq_attr_sz = sizeof(struct mq_attr);
unsigned struct_statvfs_sz = sizeof(struct statvfs);
unsigned struct_sigaltstack_sz = sizeof(stack_t);

const uptr sig_ign = (uptr)SIG_IGN;
const uptr sig_dfl = (uptr)SIG_DFL;
const uptr sig_err = (uptr)SIG_ERR;
const uptr sa_siginfo = (uptr)SA_SIGINFO;

int ptrace_pt_io = PT_IO;
int ptrace_pt_lwpinfo = PT_LWPINFO;
int ptrace_pt_set_event_mask = PT_SET_EVENT_MASK;
int ptrace_pt_get_event_mask = PT_GET_EVENT_MASK;
int ptrace_pt_get_process_state = PT_GET_PROCESS_STATE;
int ptrace_pt_set_siginfo = PT_SET_SIGINFO;
int ptrace_pt_get_siginfo = PT_GET_SIGINFO;
int ptrace_pt_set_sigmask = PT_SET_SIGMASK;
int ptrace_pt_get_sigmask = PT_GET_SIGMASK;
int ptrace_piod_read_d = PIOD_READ_D;
int ptrace_piod_write_d = PIOD_WRITE_D;
int ptrace_piod_read_i = PIOD_READ_I;
int ptrace_piod_write_i = PIOD_WRITE_I;
int ptrace_piod_read_auxv = PIOD_READ_AUXV;

#if defined(PT_SETREGS) && defined(PT_GETREGS)
int ptrace_pt_setregs = PT_SETREGS;
int ptrace_pt_getregs = PT_GETREGS;
#else
int ptrace_pt_setregs = -1;
int ptrace_pt_getregs = -1;
#endif

#if defined(PT_SETFPREGS) && defined(PT_GETFPREGS)
int ptrace_pt_setfpregs = PT_SETFPREGS;
int ptrace_pt_getfpregs = PT_GETFPREGS;
#else
int ptrace_pt_setfpregs = -1;
int ptrace_pt_getfpregs = -1;
#endif

#if defined(PT_SETDBREGS) && defined(PT_GETDBREGS)
int ptrace_pt_setdbregs = PT_SETDBREGS;
int ptrace_pt_getdbregs = PT_GETDBREGS;
#else
int ptrace_pt_setdbregs = -1;
int ptrace_pt_getdbregs = -1;
#endif

unsigned struct_ptrace_ptrace_io_desc_struct_sz = sizeof(struct ptrace_io_desc);
unsigned struct_ptrace_ptrace_lwpinfo_struct_sz = sizeof(struct ptrace_lwpinfo);
unsigned struct_ptrace_ptrace_event_struct_sz = sizeof(ptrace_event_t);
unsigned struct_ptrace_ptrace_siginfo_struct_sz = sizeof(ptrace_siginfo_t);

#if defined(PT_SETREGS)
unsigned struct_ptrace_reg_struct_sz = sizeof(struct reg);
#else
unsigned struct_ptrace_reg_struct_sz = -1;
#endif

#if defined(PT_SETFPREGS)
unsigned struct_ptrace_fpreg_struct_sz = sizeof(struct fpreg);
#else
unsigned struct_ptrace_fpreg_struct_sz = -1;
#endif

#if defined(PT_SETDBREGS)
unsigned struct_ptrace_dbreg_struct_sz = sizeof(struct dbreg);
#else
unsigned struct_ptrace_dbreg_struct_sz = -1;
#endif

int shmctl_ipc_stat = (int)IPC_STAT;

unsigned struct_utmp_sz = sizeof(struct utmp);
unsigned struct_utmpx_sz = sizeof(struct utmpx);

int map_fixed = MAP_FIXED;

int af_inet = (int)AF_INET;
int af_inet6 = (int)AF_INET6;

uptr __sanitizer_in_addr_sz(int af) {
  if (af == AF_INET)
    return sizeof(struct in_addr);
  else if (af == AF_INET6)
    return sizeof(struct in6_addr);
  else
    return 0;
}

unsigned struct_ElfW_Phdr_sz = sizeof(Elf_Phdr);

int glob_nomatch = GLOB_NOMATCH;
int glob_altdirfunc = GLOB_ALTDIRFUNC;

unsigned path_max = PATH_MAX;

int struct_ttyent_sz = sizeof(struct ttyent);

// ioctl arguments
unsigned struct_altqreq_sz = sizeof(altqreq);
unsigned struct_amr_user_ioctl_sz = sizeof(amr_user_ioctl);
unsigned struct_ap_control_sz = sizeof(ap_control);
unsigned struct_apm_ctl_sz = sizeof(apm_ctl);
unsigned struct_apm_event_info_sz = sizeof(apm_event_info);
unsigned struct_apm_power_info_sz = sizeof(apm_power_info);
unsigned struct_atabusiodetach_args_sz = sizeof(atabusiodetach_args);
unsigned struct_atabusioscan_args_sz = sizeof(atabusioscan_args);
unsigned struct_ath_diag_sz = sizeof(ath_diag);
unsigned struct_atm_flowmap_sz = sizeof(atm_flowmap);
unsigned struct_atm_pseudoioctl_sz = sizeof(atm_pseudoioctl);
unsigned struct_audio_buf_info_sz = sizeof(audio_buf_info);
unsigned struct_audio_device_sz = sizeof(audio_device);
unsigned struct_audio_encoding_sz = sizeof(audio_encoding);
unsigned struct_audio_info_sz = sizeof(audio_info);
unsigned struct_audio_offset_sz = sizeof(audio_offset);
unsigned struct_bio_locate_sz = sizeof(bio_locate);
unsigned struct_bioc_alarm_sz = sizeof(bioc_alarm);
unsigned struct_bioc_blink_sz = sizeof(bioc_blink);
unsigned struct_bioc_disk_sz = sizeof(bioc_disk);
unsigned struct_bioc_inq_sz = sizeof(bioc_inq);
unsigned struct_bioc_setstate_sz = sizeof(bioc_setstate);
unsigned struct_bioc_vol_sz = sizeof(bioc_vol);
unsigned struct_bioc_volops_sz = sizeof(bioc_volops);
unsigned struct_bktr_chnlset_sz = sizeof(bktr_chnlset);
unsigned struct_bktr_remote_sz = sizeof(bktr_remote);
unsigned struct_blue_conf_sz = sizeof(blue_conf);
unsigned struct_blue_interface_sz = sizeof(blue_interface);
unsigned struct_blue_stats_sz = sizeof(blue_stats);
unsigned struct_bpf_dltlist_sz = sizeof(bpf_dltlist);
unsigned struct_bpf_program_sz = sizeof(bpf_program);
unsigned struct_bpf_stat_old_sz = sizeof(bpf_stat_old);
unsigned struct_bpf_stat_sz = sizeof(bpf_stat);
unsigned struct_bpf_version_sz = sizeof(bpf_version);
unsigned struct_btreq_sz = sizeof(btreq);
unsigned struct_btsco_info_sz = sizeof(btsco_info);
unsigned struct_buffmem_desc_sz = sizeof(buffmem_desc);
unsigned struct_cbq_add_class_sz = sizeof(cbq_add_class);
unsigned struct_cbq_add_filter_sz = sizeof(cbq_add_filter);
unsigned struct_cbq_delete_class_sz = sizeof(cbq_delete_class);
unsigned struct_cbq_delete_filter_sz = sizeof(cbq_delete_filter);
unsigned struct_cbq_getstats_sz = sizeof(cbq_getstats);
unsigned struct_cbq_interface_sz = sizeof(cbq_interface);
unsigned struct_cbq_modify_class_sz = sizeof(cbq_modify_class);
unsigned struct_ccd_ioctl_sz = sizeof(ccd_ioctl);
unsigned struct_cdnr_add_element_sz = sizeof(cdnr_add_element);
unsigned struct_cdnr_add_filter_sz = sizeof(cdnr_add_filter);
unsigned struct_cdnr_add_tbmeter_sz = sizeof(cdnr_add_tbmeter);
unsigned struct_cdnr_add_trtcm_sz = sizeof(cdnr_add_trtcm);
unsigned struct_cdnr_add_tswtcm_sz = sizeof(cdnr_add_tswtcm);
unsigned struct_cdnr_delete_element_sz = sizeof(cdnr_delete_element);
unsigned struct_cdnr_delete_filter_sz = sizeof(cdnr_delete_filter);
unsigned struct_cdnr_get_stats_sz = sizeof(cdnr_get_stats);
unsigned struct_cdnr_interface_sz = sizeof(cdnr_interface);
unsigned struct_cdnr_modify_tbmeter_sz = sizeof(cdnr_modify_tbmeter);
unsigned struct_cdnr_modify_trtcm_sz = sizeof(cdnr_modify_trtcm);
unsigned struct_cdnr_modify_tswtcm_sz = sizeof(cdnr_modify_tswtcm);
unsigned struct_cdnr_tbmeter_stats_sz = sizeof(cdnr_tbmeter_stats);
unsigned struct_cdnr_tcm_stats_sz = sizeof(cdnr_tcm_stats);
unsigned struct_cgd_ioctl_sz = sizeof(cgd_ioctl);
unsigned struct_cgd_user_sz = sizeof(cgd_user);
unsigned struct_changer_element_status_request_sz =
    sizeof(changer_element_status_request);
unsigned struct_changer_exchange_request_sz = sizeof(changer_exchange_request);
unsigned struct_changer_move_request_sz = sizeof(changer_move_request);
unsigned struct_changer_params_sz = sizeof(changer_params);
unsigned struct_changer_position_request_sz = sizeof(changer_position_request);
unsigned struct_changer_set_voltag_request_sz =
    sizeof(changer_set_voltag_request);
unsigned struct_clockctl_adjtime_sz = sizeof(clockctl_adjtime);
unsigned struct_clockctl_clock_settime_sz = sizeof(clockctl_clock_settime);
unsigned struct_clockctl_ntp_adjtime_sz = sizeof(clockctl_ntp_adjtime);
unsigned struct_clockctl_settimeofday_sz = sizeof(clockctl_settimeofday);
unsigned struct_cnwistats_sz = sizeof(cnwistats);
unsigned struct_cnwitrail_sz = sizeof(cnwitrail);
unsigned struct_cnwstatus_sz = sizeof(cnwstatus);
unsigned struct_count_info_sz = sizeof(count_info);
unsigned struct_cpu_ucode_sz = sizeof(cpu_ucode);
unsigned struct_cpu_ucode_version_sz = sizeof(cpu_ucode_version);
unsigned struct_crypt_kop_sz = sizeof(crypt_kop);
unsigned struct_crypt_mkop_sz = sizeof(crypt_mkop);
unsigned struct_crypt_mop_sz = sizeof(crypt_mop);
unsigned struct_crypt_op_sz = sizeof(crypt_op);
unsigned struct_crypt_result_sz = sizeof(crypt_result);
unsigned struct_crypt_sfop_sz = sizeof(crypt_sfop);
unsigned struct_crypt_sgop_sz = sizeof(crypt_sgop);
unsigned struct_cryptret_sz = sizeof(cryptret);
unsigned struct_devdetachargs_sz = sizeof(devdetachargs);
unsigned struct_devlistargs_sz = sizeof(devlistargs);
unsigned struct_devpmargs_sz = sizeof(devpmargs);
unsigned struct_devrescanargs_sz = sizeof(devrescanargs);
unsigned struct_disk_badsecinfo_sz = sizeof(disk_badsecinfo);
unsigned struct_disk_strategy_sz = sizeof(disk_strategy);
unsigned struct_disklabel_sz = sizeof(disklabel);
unsigned struct_dkbad_sz = sizeof(dkbad);
unsigned struct_dkwedge_info_sz = sizeof(dkwedge_info);
unsigned struct_dkwedge_list_sz = sizeof(dkwedge_list);
unsigned struct_dmio_setfunc_sz = sizeof(dmio_setfunc);
unsigned struct_dmx_pes_filter_params_sz = sizeof(dmx_pes_filter_params);
unsigned struct_dmx_sct_filter_params_sz = sizeof(dmx_sct_filter_params);
unsigned struct_dmx_stc_sz = sizeof(dmx_stc);
unsigned struct_dvb_diseqc_master_cmd_sz = sizeof(dvb_diseqc_master_cmd);
unsigned struct_dvb_diseqc_slave_reply_sz = sizeof(dvb_diseqc_slave_reply);
unsigned struct_dvb_frontend_event_sz = sizeof(dvb_frontend_event);
unsigned struct_dvb_frontend_info_sz = sizeof(dvb_frontend_info);
unsigned struct_dvb_frontend_parameters_sz = sizeof(dvb_frontend_parameters);
unsigned struct_eccapreq_sz = sizeof(eccapreq);
unsigned struct_fbcmap_sz = sizeof(fbcmap);
unsigned struct_fbcurpos_sz = sizeof(fbcurpos);
unsigned struct_fbcursor_sz = sizeof(fbcursor);
unsigned struct_fbgattr_sz = sizeof(fbgattr);
unsigned struct_fbsattr_sz = sizeof(fbsattr);
unsigned struct_fbtype_sz = sizeof(fbtype);
unsigned struct_fdformat_cmd_sz = sizeof(fdformat_cmd);
unsigned struct_fdformat_parms_sz = sizeof(fdformat_parms);
unsigned struct_fifoq_conf_sz = sizeof(fifoq_conf);
unsigned struct_fifoq_getstats_sz = sizeof(fifoq_getstats);
unsigned struct_fifoq_interface_sz = sizeof(fifoq_interface);
unsigned struct_format_op_sz = sizeof(format_op);
unsigned struct_fss_get_sz = sizeof(fss_get);
unsigned struct_fss_set_sz = sizeof(fss_set);
unsigned struct_gpio_attach_sz = sizeof(gpio_attach);
unsigned struct_gpio_info_sz = sizeof(gpio_info);
unsigned struct_gpio_req_sz = sizeof(gpio_req);
unsigned struct_gpio_set_sz = sizeof(gpio_set);
unsigned struct_hfsc_add_class_sz = sizeof(hfsc_add_class);
unsigned struct_hfsc_add_filter_sz = sizeof(hfsc_add_filter);
unsigned struct_hfsc_attach_sz = sizeof(hfsc_attach);
unsigned struct_hfsc_class_stats_sz = sizeof(hfsc_class_stats);
unsigned struct_hfsc_delete_class_sz = sizeof(hfsc_delete_class);
unsigned struct_hfsc_delete_filter_sz = sizeof(hfsc_delete_filter);
unsigned struct_hfsc_interface_sz = sizeof(hfsc_interface);
unsigned struct_hfsc_modify_class_sz = sizeof(hfsc_modify_class);
unsigned struct_hpcfb_dsp_op_sz = sizeof(hpcfb_dsp_op);
unsigned struct_hpcfb_dspconf_sz = sizeof(hpcfb_dspconf);
unsigned struct_hpcfb_fbconf_sz = sizeof(hpcfb_fbconf);
unsigned struct_if_addrprefreq_sz = sizeof(if_addrprefreq);
unsigned struct_if_clonereq_sz = sizeof(if_clonereq);
unsigned struct_if_laddrreq_sz = sizeof(if_laddrreq);
unsigned struct_ifaddr_sz = sizeof(ifaddr);
unsigned struct_ifaliasreq_sz = sizeof(ifaliasreq);
unsigned struct_ifcapreq_sz = sizeof(ifcapreq);
unsigned struct_ifconf_sz = sizeof(ifconf);
unsigned struct_ifdatareq_sz = sizeof(ifdatareq);
unsigned struct_ifdrv_sz = sizeof(ifdrv);
unsigned struct_ifmediareq_sz = sizeof(ifmediareq);
unsigned struct_ifpppcstatsreq_sz = sizeof(ifpppcstatsreq);
unsigned struct_ifpppstatsreq_sz = sizeof(ifpppstatsreq);
unsigned struct_ifreq_sz = sizeof(ifreq);
unsigned struct_in6_addrpolicy_sz = sizeof(in6_addrpolicy);
unsigned struct_in6_ndireq_sz = sizeof(in6_ndireq);
unsigned struct_ioc_load_unload_sz = sizeof(ioc_load_unload);
unsigned struct_ioc_patch_sz = sizeof(ioc_patch);
unsigned struct_ioc_play_blocks_sz = sizeof(ioc_play_blocks);
unsigned struct_ioc_play_msf_sz = sizeof(ioc_play_msf);
unsigned struct_ioc_play_track_sz = sizeof(ioc_play_track);
unsigned struct_ioc_read_subchannel_sz = sizeof(ioc_read_subchannel);
unsigned struct_ioc_read_toc_entry_sz = sizeof(ioc_read_toc_entry);
unsigned struct_ioc_toc_header_sz = sizeof(ioc_toc_header);
unsigned struct_ioc_vol_sz = sizeof(ioc_vol);
unsigned struct_ioctl_pt_sz = sizeof(ioctl_pt);
unsigned struct_ioppt_sz = sizeof(ioppt);
unsigned struct_iovec_sz = sizeof(iovec);
unsigned struct_ipfobj_sz = sizeof(ipfobj);
unsigned struct_irda_params_sz = sizeof(irda_params);
unsigned struct_isp_fc_device_sz = sizeof(isp_fc_device);
unsigned struct_isp_fc_tsk_mgmt_sz = sizeof(isp_fc_tsk_mgmt);
unsigned struct_isp_hba_device_sz = sizeof(isp_hba_device);
unsigned struct_isv_cmd_sz = sizeof(isv_cmd);
unsigned struct_jobs_add_class_sz = sizeof(jobs_add_class);
unsigned struct_jobs_add_filter_sz = sizeof(jobs_add_filter);
unsigned struct_jobs_attach_sz = sizeof(jobs_attach);
unsigned struct_jobs_class_stats_sz = sizeof(jobs_class_stats);
unsigned struct_jobs_delete_class_sz = sizeof(jobs_delete_class);
unsigned struct_jobs_delete_filter_sz = sizeof(jobs_delete_filter);
unsigned struct_jobs_interface_sz = sizeof(jobs_interface);
unsigned struct_jobs_modify_class_sz = sizeof(jobs_modify_class);
unsigned struct_kbentry_sz = sizeof(kbentry);
unsigned struct_kfilter_mapping_sz = sizeof(kfilter_mapping);
unsigned struct_kiockeymap_sz = sizeof(kiockeymap);
unsigned struct_ksyms_gsymbol_sz = sizeof(ksyms_gsymbol);
unsigned struct_ksyms_gvalue_sz = sizeof(ksyms_gvalue);
unsigned struct_ksyms_ogsymbol_sz = sizeof(ksyms_ogsymbol);
unsigned struct_kttcp_io_args_sz = sizeof(kttcp_io_args);
unsigned struct_ltchars_sz = sizeof(ltchars);
unsigned struct_lua_create_sz = sizeof(struct lua_create);
unsigned struct_lua_info_sz = sizeof(struct lua_info);
unsigned struct_lua_load_sz = sizeof(struct lua_load);
unsigned struct_lua_require_sz = sizeof(lua_require);
unsigned struct_mbpp_param_sz = sizeof(mbpp_param);
unsigned struct_md_conf_sz = sizeof(md_conf);
unsigned struct_meteor_capframe_sz = sizeof(meteor_capframe);
unsigned struct_meteor_counts_sz = sizeof(meteor_counts);
unsigned struct_meteor_geomet_sz = sizeof(meteor_geomet);
unsigned struct_meteor_pixfmt_sz = sizeof(meteor_pixfmt);
unsigned struct_meteor_video_sz = sizeof(meteor_video);
unsigned struct_mlx_cinfo_sz = sizeof(mlx_cinfo);
unsigned struct_mlx_pause_sz = sizeof(mlx_pause);
unsigned struct_mlx_rebuild_request_sz = sizeof(mlx_rebuild_request);
unsigned struct_mlx_rebuild_status_sz = sizeof(mlx_rebuild_status);
unsigned struct_mlx_usercommand_sz = sizeof(mlx_usercommand);
unsigned struct_mly_user_command_sz = sizeof(mly_user_command);
unsigned struct_mly_user_health_sz = sizeof(mly_user_health);
unsigned struct_mtget_sz = sizeof(mtget);
unsigned struct_mtop_sz = sizeof(mtop);
unsigned struct_npf_ioctl_table_sz = sizeof(npf_ioctl_table);
unsigned struct_npioctl_sz = sizeof(npioctl);
unsigned struct_nvme_pt_command_sz = sizeof(nvme_pt_command);
unsigned struct_ochanger_element_status_request_sz =
    sizeof(ochanger_element_status_request);
unsigned struct_ofiocdesc_sz = sizeof(ofiocdesc);
unsigned struct_okiockey_sz = sizeof(okiockey);
unsigned struct_ortentry_sz = sizeof(ortentry);
unsigned struct_oscsi_addr_sz = sizeof(oscsi_addr);
unsigned struct_oss_audioinfo_sz = sizeof(oss_audioinfo);
unsigned struct_oss_sysinfo_sz = sizeof(oss_sysinfo);
unsigned struct_pciio_bdf_cfgreg_sz = sizeof(pciio_bdf_cfgreg);
unsigned struct_pciio_businfo_sz = sizeof(pciio_businfo);
unsigned struct_pciio_cfgreg_sz = sizeof(pciio_cfgreg);
unsigned struct_pciio_drvname_sz = sizeof(pciio_drvname);
unsigned struct_pciio_drvnameonbus_sz = sizeof(pciio_drvnameonbus);
unsigned struct_pcvtid_sz = sizeof(pcvtid);
unsigned struct_pf_osfp_ioctl_sz = sizeof(pf_osfp_ioctl);
unsigned struct_pf_status_sz = sizeof(pf_status);
unsigned struct_pfioc_altq_sz = sizeof(pfioc_altq);
unsigned struct_pfioc_if_sz = sizeof(pfioc_if);
unsigned struct_pfioc_iface_sz = sizeof(pfioc_iface);
unsigned struct_pfioc_limit_sz = sizeof(pfioc_limit);
unsigned struct_pfioc_natlook_sz = sizeof(pfioc_natlook);
unsigned struct_pfioc_pooladdr_sz = sizeof(pfioc_pooladdr);
unsigned struct_pfioc_qstats_sz = sizeof(pfioc_qstats);
unsigned struct_pfioc_rule_sz = sizeof(pfioc_rule);
unsigned struct_pfioc_ruleset_sz = sizeof(pfioc_ruleset);
unsigned struct_pfioc_src_node_kill_sz = sizeof(pfioc_src_node_kill);
unsigned struct_pfioc_src_nodes_sz = sizeof(pfioc_src_nodes);
unsigned struct_pfioc_state_kill_sz = sizeof(pfioc_state_kill);
unsigned struct_pfioc_state_sz = sizeof(pfioc_state);
unsigned struct_pfioc_states_sz = sizeof(pfioc_states);
unsigned struct_pfioc_table_sz = sizeof(pfioc_table);
unsigned struct_pfioc_tm_sz = sizeof(pfioc_tm);
unsigned struct_pfioc_trans_sz = sizeof(pfioc_trans);
unsigned struct_plistref_sz = sizeof(plistref);
unsigned struct_power_type_sz = sizeof(power_type);
unsigned struct_ppp_idle_sz = sizeof(ppp_idle);
unsigned struct_ppp_option_data_sz = sizeof(ppp_option_data);
unsigned struct_ppp_rawin_sz = sizeof(ppp_rawin);
unsigned struct_pppoeconnectionstate_sz = sizeof(pppoeconnectionstate);
unsigned struct_pppoediscparms_sz = sizeof(pppoediscparms);
unsigned struct_priq_add_class_sz = sizeof(priq_add_class);
unsigned struct_priq_add_filter_sz = sizeof(priq_add_filter);
unsigned struct_priq_class_stats_sz = sizeof(priq_class_stats);
unsigned struct_priq_delete_class_sz = sizeof(priq_delete_class);
unsigned struct_priq_delete_filter_sz = sizeof(priq_delete_filter);
unsigned struct_priq_interface_sz = sizeof(priq_interface);
unsigned struct_priq_modify_class_sz = sizeof(priq_modify_class);
unsigned struct_ptmget_sz = sizeof(ptmget);
unsigned struct_pvctxreq_sz = sizeof(pvctxreq);
unsigned struct_radio_info_sz = sizeof(radio_info);
unsigned struct_red_conf_sz = sizeof(red_conf);
unsigned struct_red_interface_sz = sizeof(red_interface);
unsigned struct_red_stats_sz = sizeof(red_stats);
unsigned struct_redparams_sz = sizeof(redparams);
unsigned struct_rf_pmparams_sz = sizeof(rf_pmparams);
unsigned struct_rf_pmstat_sz = sizeof(rf_pmstat);
unsigned struct_rf_recon_req_sz = sizeof(rf_recon_req);
unsigned struct_rio_conf_sz = sizeof(rio_conf);
unsigned struct_rio_interface_sz = sizeof(rio_interface);
unsigned struct_rio_stats_sz = sizeof(rio_stats);
unsigned struct_satlink_id_sz = sizeof(satlink_id);
unsigned struct_scan_io_sz = sizeof(scan_io);
unsigned struct_scbusaccel_args_sz = sizeof(scbusaccel_args);
unsigned struct_scbusiodetach_args_sz = sizeof(scbusiodetach_args);
unsigned struct_scbusioscan_args_sz = sizeof(scbusioscan_args);
unsigned struct_scsi_addr_sz = sizeof(scsi_addr);
unsigned struct_seq_event_rec_sz = sizeof(seq_event_rec);
unsigned struct_session_op_sz = sizeof(session_op);
unsigned struct_sgttyb_sz = sizeof(sgttyb);
unsigned struct_sioc_sg_req_sz = sizeof(sioc_sg_req);
unsigned struct_sioc_vif_req_sz = sizeof(sioc_vif_req);
unsigned struct_smbioc_flags_sz = sizeof(smbioc_flags);
unsigned struct_smbioc_lookup_sz = sizeof(smbioc_lookup);
unsigned struct_smbioc_oshare_sz = sizeof(smbioc_oshare);
unsigned struct_smbioc_ossn_sz = sizeof(smbioc_ossn);
unsigned struct_smbioc_rq_sz = sizeof(smbioc_rq);
unsigned struct_smbioc_rw_sz = sizeof(smbioc_rw);
unsigned struct_spppauthcfg_sz = sizeof(spppauthcfg);
unsigned struct_spppauthfailuresettings_sz = sizeof(spppauthfailuresettings);
unsigned struct_spppauthfailurestats_sz = sizeof(spppauthfailurestats);
unsigned struct_spppdnsaddrs_sz = sizeof(spppdnsaddrs);
unsigned struct_spppdnssettings_sz = sizeof(spppdnssettings);
unsigned struct_spppidletimeout_sz = sizeof(spppidletimeout);
unsigned struct_spppkeepalivesettings_sz = sizeof(spppkeepalivesettings);
unsigned struct_sppplcpcfg_sz = sizeof(sppplcpcfg);
unsigned struct_spppstatus_sz = sizeof(spppstatus);
unsigned struct_spppstatusncp_sz = sizeof(spppstatusncp);
unsigned struct_srt_rt_sz = sizeof(srt_rt);
unsigned struct_stic_xinfo_sz = sizeof(stic_xinfo);
unsigned struct_sun_dkctlr_sz = sizeof(sun_dkctlr);
unsigned struct_sun_dkgeom_sz = sizeof(sun_dkgeom);
unsigned struct_sun_dkpart_sz = sizeof(sun_dkpart);
unsigned struct_synth_info_sz = sizeof(synth_info);
unsigned struct_tbrreq_sz = sizeof(tbrreq);
unsigned struct_tchars_sz = sizeof(tchars);
unsigned struct_termios_sz = sizeof(termios);
unsigned struct_timeval_sz = sizeof(timeval);
unsigned struct_twe_drivecommand_sz = sizeof(twe_drivecommand);
unsigned struct_twe_paramcommand_sz = sizeof(twe_paramcommand);
unsigned struct_twe_usercommand_sz = sizeof(twe_usercommand);
unsigned struct_ukyopon_identify_sz = sizeof(ukyopon_identify);
unsigned struct_urio_command_sz = sizeof(urio_command);
unsigned struct_usb_alt_interface_sz = sizeof(usb_alt_interface);
unsigned struct_usb_bulk_ra_wb_opt_sz = sizeof(usb_bulk_ra_wb_opt);
unsigned struct_usb_config_desc_sz = sizeof(usb_config_desc);
unsigned struct_usb_ctl_report_desc_sz = sizeof(usb_ctl_report_desc);
unsigned struct_usb_ctl_report_sz = sizeof(usb_ctl_report);
unsigned struct_usb_ctl_request_sz = sizeof(usb_ctl_request);
unsigned struct_usb_device_info_old_sz = sizeof(usb_device_info_old);
unsigned struct_usb_device_info_sz = sizeof(usb_device_info);
unsigned struct_usb_device_stats_sz = sizeof(usb_device_stats);
unsigned struct_usb_endpoint_desc_sz = sizeof(usb_endpoint_desc);
unsigned struct_usb_full_desc_sz = sizeof(usb_full_desc);
unsigned struct_usb_interface_desc_sz = sizeof(usb_interface_desc);
unsigned struct_usb_string_desc_sz = sizeof(usb_string_desc);
unsigned struct_utoppy_readfile_sz = sizeof(utoppy_readfile);
unsigned struct_utoppy_rename_sz = sizeof(utoppy_rename);
unsigned struct_utoppy_stats_sz = sizeof(utoppy_stats);
unsigned struct_utoppy_writefile_sz = sizeof(utoppy_writefile);
unsigned struct_v4l2_audio_sz = sizeof(v4l2_audio);
unsigned struct_v4l2_audioout_sz = sizeof(v4l2_audioout);
unsigned struct_v4l2_buffer_sz = sizeof(v4l2_buffer);
unsigned struct_v4l2_capability_sz = sizeof(v4l2_capability);
unsigned struct_v4l2_control_sz = sizeof(v4l2_control);
unsigned struct_v4l2_crop_sz = sizeof(v4l2_crop);
unsigned struct_v4l2_cropcap_sz = sizeof(v4l2_cropcap);
unsigned struct_v4l2_fmtdesc_sz = sizeof(v4l2_fmtdesc);
unsigned struct_v4l2_format_sz = sizeof(v4l2_format);
unsigned struct_v4l2_framebuffer_sz = sizeof(v4l2_framebuffer);
unsigned struct_v4l2_frequency_sz = sizeof(v4l2_frequency);
unsigned struct_v4l2_frmivalenum_sz = sizeof(v4l2_frmivalenum);
unsigned struct_v4l2_frmsizeenum_sz = sizeof(v4l2_frmsizeenum);
unsigned struct_v4l2_input_sz = sizeof(v4l2_input);
unsigned struct_v4l2_jpegcompression_sz = sizeof(v4l2_jpegcompression);
unsigned struct_v4l2_modulator_sz = sizeof(v4l2_modulator);
unsigned struct_v4l2_output_sz = sizeof(v4l2_output);
unsigned struct_v4l2_queryctrl_sz = sizeof(v4l2_queryctrl);
unsigned struct_v4l2_querymenu_sz = sizeof(v4l2_querymenu);
unsigned struct_v4l2_requestbuffers_sz = sizeof(v4l2_requestbuffers);
unsigned struct_v4l2_standard_sz = sizeof(v4l2_standard);
unsigned struct_v4l2_streamparm_sz = sizeof(v4l2_streamparm);
unsigned struct_v4l2_tuner_sz = sizeof(v4l2_tuner);
unsigned struct_vnd_ioctl_sz = sizeof(vnd_ioctl);
unsigned struct_vnd_user_sz = sizeof(vnd_user);
unsigned struct_vt_stat_sz = sizeof(vt_stat);
unsigned struct_wdog_conf_sz = sizeof(wdog_conf);
unsigned struct_wdog_mode_sz = sizeof(wdog_mode);
unsigned struct_wfq_conf_sz = sizeof(wfq_conf);
unsigned struct_wfq_getqid_sz = sizeof(wfq_getqid);
unsigned struct_wfq_getstats_sz = sizeof(wfq_getstats);
unsigned struct_wfq_interface_sz = sizeof(wfq_interface);
unsigned struct_wfq_setweight_sz = sizeof(wfq_setweight);
unsigned struct_winsize_sz = sizeof(winsize);
unsigned struct_wscons_event_sz = sizeof(wscons_event);
unsigned struct_wsdisplay_addscreendata_sz = sizeof(wsdisplay_addscreendata);
unsigned struct_wsdisplay_char_sz = sizeof(wsdisplay_char);
unsigned struct_wsdisplay_cmap_sz = sizeof(wsdisplay_cmap);
unsigned struct_wsdisplay_curpos_sz = sizeof(wsdisplay_curpos);
unsigned struct_wsdisplay_cursor_sz = sizeof(wsdisplay_cursor);
unsigned struct_wsdisplay_delscreendata_sz = sizeof(wsdisplay_delscreendata);
unsigned struct_wsdisplay_fbinfo_sz = sizeof(wsdisplay_fbinfo);
unsigned struct_wsdisplay_font_sz = sizeof(wsdisplay_font);
unsigned struct_wsdisplay_kbddata_sz = sizeof(wsdisplay_kbddata);
unsigned struct_wsdisplay_msgattrs_sz = sizeof(wsdisplay_msgattrs);
unsigned struct_wsdisplay_param_sz = sizeof(wsdisplay_param);
unsigned struct_wsdisplay_scroll_data_sz = sizeof(wsdisplay_scroll_data);
unsigned struct_wsdisplay_usefontdata_sz = sizeof(wsdisplay_usefontdata);
unsigned struct_wsdisplayio_blit_sz = sizeof(wsdisplayio_blit);
unsigned struct_wsdisplayio_bus_id_sz = sizeof(wsdisplayio_bus_id);
unsigned struct_wsdisplayio_edid_info_sz = sizeof(wsdisplayio_edid_info);
unsigned struct_wsdisplayio_fbinfo_sz = sizeof(wsdisplayio_fbinfo);
unsigned struct_wskbd_bell_data_sz = sizeof(wskbd_bell_data);
unsigned struct_wskbd_keyrepeat_data_sz = sizeof(wskbd_keyrepeat_data);
unsigned struct_wskbd_map_data_sz = sizeof(wskbd_map_data);
unsigned struct_wskbd_scroll_data_sz = sizeof(wskbd_scroll_data);
unsigned struct_wsmouse_calibcoords_sz = sizeof(wsmouse_calibcoords);
unsigned struct_wsmouse_id_sz = sizeof(wsmouse_id);
unsigned struct_wsmouse_repeat_sz = sizeof(wsmouse_repeat);
unsigned struct_wsmux_device_list_sz = sizeof(wsmux_device_list);
unsigned struct_wsmux_device_sz = sizeof(wsmux_device);
unsigned struct_xd_iocmd_sz = sizeof(xd_iocmd);

unsigned struct_scsireq_sz = sizeof(struct scsireq);
unsigned struct_tone_sz = sizeof(tone_t);
unsigned union_twe_statrequest_sz = sizeof(union twe_statrequest);
unsigned struct_usb_device_descriptor_sz = sizeof(usb_device_descriptor_t);
unsigned struct_vt_mode_sz = sizeof(struct vt_mode);
unsigned struct__old_mixer_info_sz = sizeof(struct _old_mixer_info);
unsigned struct__agp_allocate_sz = sizeof(struct _agp_allocate);
unsigned struct__agp_bind_sz = sizeof(struct _agp_bind);
unsigned struct__agp_info_sz = sizeof(struct _agp_info);
unsigned struct__agp_setup_sz = sizeof(struct _agp_setup);
unsigned struct__agp_unbind_sz = sizeof(struct _agp_unbind);
unsigned struct_atareq_sz = sizeof(struct atareq);
unsigned struct_cpustate_sz = sizeof(struct cpustate);
unsigned struct_dmx_caps_sz = sizeof(struct dmx_caps);
unsigned enum_dmx_source_sz = sizeof(dmx_source_t);
unsigned union_dvd_authinfo_sz = sizeof(dvd_authinfo);
unsigned union_dvd_struct_sz = sizeof(dvd_struct);
unsigned enum_v4l2_priority_sz = sizeof(enum v4l2_priority);
unsigned struct_envsys_basic_info_sz = sizeof(struct envsys_basic_info);
unsigned struct_envsys_tre_data_sz = sizeof(struct envsys_tre_data);
unsigned enum_fe_sec_mini_cmd_sz = sizeof(enum fe_sec_mini_cmd);
unsigned enum_fe_sec_tone_mode_sz = sizeof(enum fe_sec_tone_mode);
unsigned enum_fe_sec_voltage_sz = sizeof(enum fe_sec_voltage);
unsigned enum_fe_status_sz = sizeof(enum fe_status);
unsigned struct_gdt_ctrt_sz = sizeof(struct gdt_ctrt);
unsigned struct_gdt_event_sz = sizeof(struct gdt_event);
unsigned struct_gdt_osv_sz = sizeof(struct gdt_osv);
unsigned struct_gdt_rescan_sz = sizeof(struct gdt_rescan);
unsigned struct_gdt_statist_sz = sizeof(struct gdt_statist);
unsigned struct_gdt_ucmd_sz = sizeof(struct gdt_ucmd);
unsigned struct_iscsi_conn_status_parameters_sz =
    sizeof(iscsi_conn_status_parameters_t);
unsigned struct_iscsi_get_version_parameters_sz =
    sizeof(iscsi_get_version_parameters_t);
unsigned struct_iscsi_iocommand_parameters_sz =
    sizeof(iscsi_iocommand_parameters_t);
unsigned struct_iscsi_login_parameters_sz = sizeof(iscsi_login_parameters_t);
unsigned struct_iscsi_logout_parameters_sz = sizeof(iscsi_logout_parameters_t);
unsigned struct_iscsi_register_event_parameters_sz =
    sizeof(iscsi_register_event_parameters_t);
unsigned struct_iscsi_remove_parameters_sz = sizeof(iscsi_remove_parameters_t);
unsigned struct_iscsi_send_targets_parameters_sz =
    sizeof(iscsi_send_targets_parameters_t);
unsigned struct_iscsi_set_node_name_parameters_sz =
    sizeof(iscsi_set_node_name_parameters_t);
unsigned struct_iscsi_wait_event_parameters_sz =
    sizeof(iscsi_wait_event_parameters_t);
unsigned struct_isp_stats_sz = sizeof(isp_stats_t);
unsigned struct_lsenable_sz = sizeof(struct lsenable);
unsigned struct_lsdisable_sz = sizeof(struct lsdisable);
unsigned struct_mixer_ctrl_sz = sizeof(struct mixer_ctrl);
unsigned struct_mixer_devinfo_sz = sizeof(struct mixer_devinfo);
unsigned struct_mpu_command_rec_sz = sizeof(mpu_command_rec);
unsigned struct_rndstat_sz = sizeof(rndstat_t);
unsigned struct_rndstat_name_sz = sizeof(rndstat_name_t);
unsigned struct_rndctl_sz = sizeof(rndctl_t);
unsigned struct_rnddata_sz = sizeof(rnddata_t);
unsigned struct_rndpoolstat_sz = sizeof(rndpoolstat_t);
unsigned struct_rndstat_est_sz = sizeof(rndstat_est_t);
unsigned struct_rndstat_est_name_sz = sizeof(rndstat_est_name_t);
unsigned struct_pps_params_sz = sizeof(pps_params_t);
unsigned struct_pps_info_sz = sizeof(pps_info_t);
unsigned struct_mixer_info_sz = sizeof(struct mixer_info);
unsigned struct_RF_SparetWait_sz = sizeof(RF_SparetWait_t);
unsigned struct_RF_ComponentLabel_sz = sizeof(RF_ComponentLabel_t);
unsigned struct_RF_SingleComponent_sz = sizeof(RF_SingleComponent_t);
unsigned struct_RF_ProgressInfo_sz = sizeof(RF_ProgressInfo_t);

const unsigned IOCTL_NOT_PRESENT = 0;

unsigned IOCTL_AFM_ADDFMAP = AFM_ADDFMAP;
unsigned IOCTL_AFM_DELFMAP = AFM_DELFMAP;
unsigned IOCTL_AFM_CLEANFMAP = AFM_CLEANFMAP;
unsigned IOCTL_AFM_GETFMAP = AFM_GETFMAP;
unsigned IOCTL_ALTQGTYPE = ALTQGTYPE;
unsigned IOCTL_ALTQTBRSET = ALTQTBRSET;
unsigned IOCTL_ALTQTBRGET = ALTQTBRGET;
unsigned IOCTL_BLUE_IF_ATTACH = BLUE_IF_ATTACH;
unsigned IOCTL_BLUE_IF_DETACH = BLUE_IF_DETACH;
unsigned IOCTL_BLUE_ENABLE = BLUE_ENABLE;
unsigned IOCTL_BLUE_DISABLE = BLUE_DISABLE;
unsigned IOCTL_BLUE_CONFIG = BLUE_CONFIG;
unsigned IOCTL_BLUE_GETSTATS = BLUE_GETSTATS;
unsigned IOCTL_CBQ_IF_ATTACH = CBQ_IF_ATTACH;
unsigned IOCTL_CBQ_IF_DETACH = CBQ_IF_DETACH;
unsigned IOCTL_CBQ_ENABLE = CBQ_ENABLE;
unsigned IOCTL_CBQ_DISABLE = CBQ_DISABLE;
unsigned IOCTL_CBQ_CLEAR_HIERARCHY = CBQ_CLEAR_HIERARCHY;
unsigned IOCTL_CBQ_ADD_CLASS = CBQ_ADD_CLASS;
unsigned IOCTL_CBQ_DEL_CLASS = CBQ_DEL_CLASS;
unsigned IOCTL_CBQ_MODIFY_CLASS = CBQ_MODIFY_CLASS;
unsigned IOCTL_CBQ_ADD_FILTER = CBQ_ADD_FILTER;
unsigned IOCTL_CBQ_DEL_FILTER = CBQ_DEL_FILTER;
unsigned IOCTL_CBQ_GETSTATS = CBQ_GETSTATS;
unsigned IOCTL_CDNR_IF_ATTACH = CDNR_IF_ATTACH;
unsigned IOCTL_CDNR_IF_DETACH = CDNR_IF_DETACH;
unsigned IOCTL_CDNR_ENABLE = CDNR_ENABLE;
unsigned IOCTL_CDNR_DISABLE = CDNR_DISABLE;
unsigned IOCTL_CDNR_ADD_FILTER = CDNR_ADD_FILTER;
unsigned IOCTL_CDNR_DEL_FILTER = CDNR_DEL_FILTER;
unsigned IOCTL_CDNR_GETSTATS = CDNR_GETSTATS;
unsigned IOCTL_CDNR_ADD_ELEM = CDNR_ADD_ELEM;
unsigned IOCTL_CDNR_DEL_ELEM = CDNR_DEL_ELEM;
unsigned IOCTL_CDNR_ADD_TBM = CDNR_ADD_TBM;
unsigned IOCTL_CDNR_MOD_TBM = CDNR_MOD_TBM;
unsigned IOCTL_CDNR_TBM_STATS = CDNR_TBM_STATS;
unsigned IOCTL_CDNR_ADD_TCM = CDNR_ADD_TCM;
unsigned IOCTL_CDNR_MOD_TCM = CDNR_MOD_TCM;
unsigned IOCTL_CDNR_TCM_STATS = CDNR_TCM_STATS;
unsigned IOCTL_CDNR_ADD_TSW = CDNR_ADD_TSW;
unsigned IOCTL_CDNR_MOD_TSW = CDNR_MOD_TSW;
unsigned IOCTL_FIFOQ_IF_ATTACH = FIFOQ_IF_ATTACH;
unsigned IOCTL_FIFOQ_IF_DETACH = FIFOQ_IF_DETACH;
unsigned IOCTL_FIFOQ_ENABLE = FIFOQ_ENABLE;
unsigned IOCTL_FIFOQ_DISABLE = FIFOQ_DISABLE;
unsigned IOCTL_FIFOQ_CONFIG = FIFOQ_CONFIG;
unsigned IOCTL_FIFOQ_GETSTATS = FIFOQ_GETSTATS;
unsigned IOCTL_HFSC_IF_ATTACH = HFSC_IF_ATTACH;
unsigned IOCTL_HFSC_IF_DETACH = HFSC_IF_DETACH;
unsigned IOCTL_HFSC_ENABLE = HFSC_ENABLE;
unsigned IOCTL_HFSC_DISABLE = HFSC_DISABLE;
unsigned IOCTL_HFSC_CLEAR_HIERARCHY = HFSC_CLEAR_HIERARCHY;
unsigned IOCTL_HFSC_ADD_CLASS = HFSC_ADD_CLASS;
unsigned IOCTL_HFSC_DEL_CLASS = HFSC_DEL_CLASS;
unsigned IOCTL_HFSC_MOD_CLASS = HFSC_MOD_CLASS;
unsigned IOCTL_HFSC_ADD_FILTER = HFSC_ADD_FILTER;
unsigned IOCTL_HFSC_DEL_FILTER = HFSC_DEL_FILTER;
unsigned IOCTL_HFSC_GETSTATS = HFSC_GETSTATS;
unsigned IOCTL_JOBS_IF_ATTACH = JOBS_IF_ATTACH;
unsigned IOCTL_JOBS_IF_DETACH = JOBS_IF_DETACH;
unsigned IOCTL_JOBS_ENABLE = JOBS_ENABLE;
unsigned IOCTL_JOBS_DISABLE = JOBS_DISABLE;
unsigned IOCTL_JOBS_CLEAR = JOBS_CLEAR;
unsigned IOCTL_JOBS_ADD_CLASS = JOBS_ADD_CLASS;
unsigned IOCTL_JOBS_DEL_CLASS = JOBS_DEL_CLASS;
unsigned IOCTL_JOBS_MOD_CLASS = JOBS_MOD_CLASS;
unsigned IOCTL_JOBS_ADD_FILTER = JOBS_ADD_FILTER;
unsigned IOCTL_JOBS_DEL_FILTER = JOBS_DEL_FILTER;
unsigned IOCTL_JOBS_GETSTATS = JOBS_GETSTATS;
unsigned IOCTL_PRIQ_IF_ATTACH = PRIQ_IF_ATTACH;
unsigned IOCTL_PRIQ_IF_DETACH = PRIQ_IF_DETACH;
unsigned IOCTL_PRIQ_ENABLE = PRIQ_ENABLE;
unsigned IOCTL_PRIQ_DISABLE = PRIQ_DISABLE;
unsigned IOCTL_PRIQ_CLEAR = PRIQ_CLEAR;
unsigned IOCTL_PRIQ_ADD_CLASS = PRIQ_ADD_CLASS;
unsigned IOCTL_PRIQ_DEL_CLASS = PRIQ_DEL_CLASS;
unsigned IOCTL_PRIQ_MOD_CLASS = PRIQ_MOD_CLASS;
unsigned IOCTL_PRIQ_ADD_FILTER = PRIQ_ADD_FILTER;
unsigned IOCTL_PRIQ_DEL_FILTER = PRIQ_DEL_FILTER;
unsigned IOCTL_PRIQ_GETSTATS = PRIQ_GETSTATS;
unsigned IOCTL_RED_IF_ATTACH = RED_IF_ATTACH;
unsigned IOCTL_RED_IF_DETACH = RED_IF_DETACH;
unsigned IOCTL_RED_ENABLE = RED_ENABLE;
unsigned IOCTL_RED_DISABLE = RED_DISABLE;
unsigned IOCTL_RED_CONFIG = RED_CONFIG;
unsigned IOCTL_RED_GETSTATS = RED_GETSTATS;
unsigned IOCTL_RED_SETDEFAULTS = RED_SETDEFAULTS;
unsigned IOCTL_RIO_IF_ATTACH = RIO_IF_ATTACH;
unsigned IOCTL_RIO_IF_DETACH = RIO_IF_DETACH;
unsigned IOCTL_RIO_ENABLE = RIO_ENABLE;
unsigned IOCTL_RIO_DISABLE = RIO_DISABLE;
unsigned IOCTL_RIO_CONFIG = RIO_CONFIG;
unsigned IOCTL_RIO_GETSTATS = RIO_GETSTATS;
unsigned IOCTL_RIO_SETDEFAULTS = RIO_SETDEFAULTS;
unsigned IOCTL_WFQ_IF_ATTACH = WFQ_IF_ATTACH;
unsigned IOCTL_WFQ_IF_DETACH = WFQ_IF_DETACH;
unsigned IOCTL_WFQ_ENABLE = WFQ_ENABLE;
unsigned IOCTL_WFQ_DISABLE = WFQ_DISABLE;
unsigned IOCTL_WFQ_CONFIG = WFQ_CONFIG;
unsigned IOCTL_WFQ_GET_STATS = WFQ_GET_STATS;
unsigned IOCTL_WFQ_GET_QID = WFQ_GET_QID;
unsigned IOCTL_WFQ_SET_WEIGHT = WFQ_SET_WEIGHT;
unsigned IOCTL_CRIOGET = CRIOGET;
unsigned IOCTL_CIOCFSESSION = CIOCFSESSION;
unsigned IOCTL_CIOCKEY = CIOCKEY;
unsigned IOCTL_CIOCNFKEYM = CIOCNFKEYM;
unsigned IOCTL_CIOCNFSESSION = CIOCNFSESSION;
unsigned IOCTL_CIOCNCRYPTRETM = CIOCNCRYPTRETM;
unsigned IOCTL_CIOCNCRYPTRET = CIOCNCRYPTRET;
unsigned IOCTL_CIOCGSESSION = CIOCGSESSION;
unsigned IOCTL_CIOCNGSESSION = CIOCNGSESSION;
unsigned IOCTL_CIOCCRYPT = CIOCCRYPT;
unsigned IOCTL_CIOCNCRYPTM = CIOCNCRYPTM;
unsigned IOCTL_CIOCASYMFEAT = CIOCASYMFEAT;
unsigned IOCTL_APM_IOC_REJECT = APM_IOC_REJECT;
unsigned IOCTL_APM_IOC_STANDBY = APM_IOC_STANDBY;
unsigned IOCTL_APM_IOC_SUSPEND = APM_IOC_SUSPEND;
unsigned IOCTL_OAPM_IOC_GETPOWER = OAPM_IOC_GETPOWER;
unsigned IOCTL_APM_IOC_GETPOWER = APM_IOC_GETPOWER;
unsigned IOCTL_APM_IOC_NEXTEVENT = APM_IOC_NEXTEVENT;
unsigned IOCTL_APM_IOC_DEV_CTL = APM_IOC_DEV_CTL;
unsigned IOCTL_NETBSD_DM_IOCTL = NETBSD_DM_IOCTL;
unsigned IOCTL_DMIO_SETFUNC = DMIO_SETFUNC;
unsigned IOCTL_DMX_START = DMX_START;
unsigned IOCTL_DMX_STOP = DMX_STOP;
unsigned IOCTL_DMX_SET_FILTER = DMX_SET_FILTER;
unsigned IOCTL_DMX_SET_PES_FILTER = DMX_SET_PES_FILTER;
unsigned IOCTL_DMX_SET_BUFFER_SIZE = DMX_SET_BUFFER_SIZE;
unsigned IOCTL_DMX_GET_STC = DMX_GET_STC;
unsigned IOCTL_DMX_ADD_PID = DMX_ADD_PID;
unsigned IOCTL_DMX_REMOVE_PID = DMX_REMOVE_PID;
unsigned IOCTL_DMX_GET_CAPS = DMX_GET_CAPS;
unsigned IOCTL_DMX_SET_SOURCE = DMX_SET_SOURCE;
unsigned IOCTL_FE_READ_STATUS = FE_READ_STATUS;
unsigned IOCTL_FE_READ_BER = FE_READ_BER;
unsigned IOCTL_FE_READ_SNR = FE_READ_SNR;
unsigned IOCTL_FE_READ_SIGNAL_STRENGTH = FE_READ_SIGNAL_STRENGTH;
unsigned IOCTL_FE_READ_UNCORRECTED_BLOCKS = FE_READ_UNCORRECTED_BLOCKS;
unsigned IOCTL_FE_SET_FRONTEND = FE_SET_FRONTEND;
unsigned IOCTL_FE_GET_FRONTEND = FE_GET_FRONTEND;
unsigned IOCTL_FE_GET_EVENT = FE_GET_EVENT;
unsigned IOCTL_FE_GET_INFO = FE_GET_INFO;
unsigned IOCTL_FE_DISEQC_RESET_OVERLOAD = FE_DISEQC_RESET_OVERLOAD;
unsigned IOCTL_FE_DISEQC_SEND_MASTER_CMD = FE_DISEQC_SEND_MASTER_CMD;
unsigned IOCTL_FE_DISEQC_RECV_SLAVE_REPLY = FE_DISEQC_RECV_SLAVE_REPLY;
unsigned IOCTL_FE_DISEQC_SEND_BURST = FE_DISEQC_SEND_BURST;
unsigned IOCTL_FE_SET_TONE = FE_SET_TONE;
unsigned IOCTL_FE_SET_VOLTAGE = FE_SET_VOLTAGE;
unsigned IOCTL_FE_ENABLE_HIGH_LNB_VOLTAGE = FE_ENABLE_HIGH_LNB_VOLTAGE;
unsigned IOCTL_FE_SET_FRONTEND_TUNE_MODE = FE_SET_FRONTEND_TUNE_MODE;
unsigned IOCTL_FE_DISHNETWORK_SEND_LEGACY_CMD = FE_DISHNETWORK_SEND_LEGACY_CMD;
unsigned IOCTL_FILEMON_SET_FD = FILEMON_SET_FD;
unsigned IOCTL_FILEMON_SET_PID = FILEMON_SET_PID;
unsigned IOCTL_HDAUDIO_FGRP_INFO = HDAUDIO_FGRP_INFO;
unsigned IOCTL_HDAUDIO_FGRP_GETCONFIG = HDAUDIO_FGRP_GETCONFIG;
unsigned IOCTL_HDAUDIO_FGRP_SETCONFIG = HDAUDIO_FGRP_SETCONFIG;
unsigned IOCTL_HDAUDIO_FGRP_WIDGET_INFO = HDAUDIO_FGRP_WIDGET_INFO;
unsigned IOCTL_HDAUDIO_FGRP_CODEC_INFO = HDAUDIO_FGRP_CODEC_INFO;
unsigned IOCTL_HDAUDIO_AFG_WIDGET_INFO = HDAUDIO_AFG_WIDGET_INFO;
unsigned IOCTL_HDAUDIO_AFG_CODEC_INFO = HDAUDIO_AFG_CODEC_INFO;
unsigned IOCTL_CEC_GET_PHYS_ADDR = CEC_GET_PHYS_ADDR;
unsigned IOCTL_CEC_GET_LOG_ADDRS = CEC_GET_LOG_ADDRS;
unsigned IOCTL_CEC_SET_LOG_ADDRS = CEC_SET_LOG_ADDRS;
unsigned IOCTL_CEC_GET_VENDOR_ID = CEC_GET_VENDOR_ID;
unsigned IOCTL_HPCFBIO_GCONF = HPCFBIO_GCONF;
unsigned IOCTL_HPCFBIO_SCONF = HPCFBIO_SCONF;
unsigned IOCTL_HPCFBIO_GDSPCONF = HPCFBIO_GDSPCONF;
unsigned IOCTL_HPCFBIO_SDSPCONF = HPCFBIO_SDSPCONF;
unsigned IOCTL_HPCFBIO_GOP = HPCFBIO_GOP;
unsigned IOCTL_HPCFBIO_SOP = HPCFBIO_SOP;
unsigned IOCTL_IOPIOCPT = IOPIOCPT;
unsigned IOCTL_IOPIOCGLCT = IOPIOCGLCT;
unsigned IOCTL_IOPIOCGSTATUS = IOPIOCGSTATUS;
unsigned IOCTL_IOPIOCRECONFIG = IOPIOCRECONFIG;
unsigned IOCTL_IOPIOCGTIDMAP = IOPIOCGTIDMAP;
unsigned IOCTL_SIOCGATHSTATS = SIOCGATHSTATS;
unsigned IOCTL_SIOCGATHDIAG = SIOCGATHDIAG;
unsigned IOCTL_METEORCAPTUR = METEORCAPTUR;
unsigned IOCTL_METEORCAPFRM = METEORCAPFRM;
unsigned IOCTL_METEORSETGEO = METEORSETGEO;
unsigned IOCTL_METEORGETGEO = METEORGETGEO;
unsigned IOCTL_METEORSTATUS = METEORSTATUS;
unsigned IOCTL_METEORSHUE = METEORSHUE;
unsigned IOCTL_METEORGHUE = METEORGHUE;
unsigned IOCTL_METEORSFMT = METEORSFMT;
unsigned IOCTL_METEORGFMT = METEORGFMT;
unsigned IOCTL_METEORSINPUT = METEORSINPUT;
unsigned IOCTL_METEORGINPUT = METEORGINPUT;
unsigned IOCTL_METEORSCHCV = METEORSCHCV;
unsigned IOCTL_METEORGCHCV = METEORGCHCV;
unsigned IOCTL_METEORSCOUNT = METEORSCOUNT;
unsigned IOCTL_METEORGCOUNT = METEORGCOUNT;
unsigned IOCTL_METEORSFPS = METEORSFPS;
unsigned IOCTL_METEORGFPS = METEORGFPS;
unsigned IOCTL_METEORSSIGNAL = METEORSSIGNAL;
unsigned IOCTL_METEORGSIGNAL = METEORGSIGNAL;
unsigned IOCTL_METEORSVIDEO = METEORSVIDEO;
unsigned IOCTL_METEORGVIDEO = METEORGVIDEO;
unsigned IOCTL_METEORSBRIG = METEORSBRIG;
unsigned IOCTL_METEORGBRIG = METEORGBRIG;
unsigned IOCTL_METEORSCSAT = METEORSCSAT;
unsigned IOCTL_METEORGCSAT = METEORGCSAT;
unsigned IOCTL_METEORSCONT = METEORSCONT;
unsigned IOCTL_METEORGCONT = METEORGCONT;
unsigned IOCTL_METEORSHWS = METEORSHWS;
unsigned IOCTL_METEORGHWS = METEORGHWS;
unsigned IOCTL_METEORSVWS = METEORSVWS;
unsigned IOCTL_METEORGVWS = METEORGVWS;
unsigned IOCTL_METEORSTS = METEORSTS;
unsigned IOCTL_METEORGTS = METEORGTS;
unsigned IOCTL_TVTUNER_SETCHNL = TVTUNER_SETCHNL;
unsigned IOCTL_TVTUNER_GETCHNL = TVTUNER_GETCHNL;
unsigned IOCTL_TVTUNER_SETTYPE = TVTUNER_SETTYPE;
unsigned IOCTL_TVTUNER_GETTYPE = TVTUNER_GETTYPE;
unsigned IOCTL_TVTUNER_GETSTATUS = TVTUNER_GETSTATUS;
unsigned IOCTL_TVTUNER_SETFREQ = TVTUNER_SETFREQ;
unsigned IOCTL_TVTUNER_GETFREQ = TVTUNER_GETFREQ;
unsigned IOCTL_TVTUNER_SETAFC = TVTUNER_SETAFC;
unsigned IOCTL_TVTUNER_GETAFC = TVTUNER_GETAFC;
unsigned IOCTL_RADIO_SETMODE = RADIO_SETMODE;
unsigned IOCTL_RADIO_GETMODE = RADIO_GETMODE;
unsigned IOCTL_RADIO_SETFREQ = RADIO_SETFREQ;
unsigned IOCTL_RADIO_GETFREQ = RADIO_GETFREQ;
unsigned IOCTL_METEORSACTPIXFMT = METEORSACTPIXFMT;
unsigned IOCTL_METEORGACTPIXFMT = METEORGACTPIXFMT;
unsigned IOCTL_METEORGSUPPIXFMT = METEORGSUPPIXFMT;
unsigned IOCTL_TVTUNER_GETCHNLSET = TVTUNER_GETCHNLSET;
unsigned IOCTL_REMOTE_GETKEY = REMOTE_GETKEY;
unsigned IOCTL_GDT_IOCTL_GENERAL = GDT_IOCTL_GENERAL;
unsigned IOCTL_GDT_IOCTL_DRVERS = GDT_IOCTL_DRVERS;
unsigned IOCTL_GDT_IOCTL_CTRTYPE = GDT_IOCTL_CTRTYPE;
unsigned IOCTL_GDT_IOCTL_OSVERS = GDT_IOCTL_OSVERS;
unsigned IOCTL_GDT_IOCTL_CTRCNT = GDT_IOCTL_CTRCNT;
unsigned IOCTL_GDT_IOCTL_EVENT = GDT_IOCTL_EVENT;
unsigned IOCTL_GDT_IOCTL_STATIST = GDT_IOCTL_STATIST;
unsigned IOCTL_GDT_IOCTL_RESCAN = GDT_IOCTL_RESCAN;
unsigned IOCTL_ISP_SDBLEV = ISP_SDBLEV;
unsigned IOCTL_ISP_RESETHBA = ISP_RESETHBA;
unsigned IOCTL_ISP_RESCAN = ISP_RESCAN;
unsigned IOCTL_ISP_SETROLE = ISP_SETROLE;
unsigned IOCTL_ISP_GETROLE = ISP_GETROLE;
unsigned IOCTL_ISP_GET_STATS = ISP_GET_STATS;
unsigned IOCTL_ISP_CLR_STATS = ISP_CLR_STATS;
unsigned IOCTL_ISP_FC_LIP = ISP_FC_LIP;
unsigned IOCTL_ISP_FC_GETDINFO = ISP_FC_GETDINFO;
unsigned IOCTL_ISP_GET_FW_CRASH_DUMP = ISP_GET_FW_CRASH_DUMP;
unsigned IOCTL_ISP_FORCE_CRASH_DUMP = ISP_FORCE_CRASH_DUMP;
unsigned IOCTL_ISP_FC_GETHINFO = ISP_FC_GETHINFO;
unsigned IOCTL_ISP_TSK_MGMT = ISP_TSK_MGMT;
unsigned IOCTL_ISP_FC_GETDLIST = ISP_FC_GETDLIST;
unsigned IOCTL_MLXD_STATUS = MLXD_STATUS;
unsigned IOCTL_MLXD_CHECKASYNC = MLXD_CHECKASYNC;
unsigned IOCTL_MLXD_DETACH = MLXD_DETACH;
unsigned IOCTL_MLX_RESCAN_DRIVES = MLX_RESCAN_DRIVES;
unsigned IOCTL_MLX_PAUSE_CHANNEL = MLX_PAUSE_CHANNEL;
unsigned IOCTL_MLX_COMMAND = MLX_COMMAND;
unsigned IOCTL_MLX_REBUILDASYNC = MLX_REBUILDASYNC;
unsigned IOCTL_MLX_REBUILDSTAT = MLX_REBUILDSTAT;
unsigned IOCTL_MLX_GET_SYSDRIVE = MLX_GET_SYSDRIVE;
unsigned IOCTL_MLX_GET_CINFO = MLX_GET_CINFO;
unsigned IOCTL_NVME_PASSTHROUGH_CMD = NVME_PASSTHROUGH_CMD;
unsigned IOCTL_IRDA_RESET_PARAMS = IRDA_RESET_PARAMS;
unsigned IOCTL_IRDA_SET_PARAMS = IRDA_SET_PARAMS;
unsigned IOCTL_IRDA_GET_SPEEDMASK = IRDA_GET_SPEEDMASK;
unsigned IOCTL_IRDA_GET_TURNAROUNDMASK = IRDA_GET_TURNAROUNDMASK;
unsigned IOCTL_IRFRAMETTY_GET_DEVICE = IRFRAMETTY_GET_DEVICE;
unsigned IOCTL_IRFRAMETTY_GET_DONGLE = IRFRAMETTY_GET_DONGLE;
unsigned IOCTL_IRFRAMETTY_SET_DONGLE = IRFRAMETTY_SET_DONGLE;
unsigned IOCTL_SATIORESET = SATIORESET;
unsigned IOCTL_SATIOGID = SATIOGID;
unsigned IOCTL_SATIOSBUFSIZE = SATIOSBUFSIZE;
unsigned IOCTL_ISV_CMD = ISV_CMD;
unsigned IOCTL_WTQICMD = WTQICMD;
unsigned IOCTL_ISCSI_GET_VERSION = ISCSI_GET_VERSION;
unsigned IOCTL_ISCSI_LOGIN = ISCSI_LOGIN;
unsigned IOCTL_ISCSI_LOGOUT = ISCSI_LOGOUT;
unsigned IOCTL_ISCSI_ADD_CONNECTION = ISCSI_ADD_CONNECTION;
unsigned IOCTL_ISCSI_RESTORE_CONNECTION = ISCSI_RESTORE_CONNECTION;
unsigned IOCTL_ISCSI_REMOVE_CONNECTION = ISCSI_REMOVE_CONNECTION;
unsigned IOCTL_ISCSI_CONNECTION_STATUS = ISCSI_CONNECTION_STATUS;
unsigned IOCTL_ISCSI_SEND_TARGETS = ISCSI_SEND_TARGETS;
unsigned IOCTL_ISCSI_SET_NODE_NAME = ISCSI_SET_NODE_NAME;
unsigned IOCTL_ISCSI_IO_COMMAND = ISCSI_IO_COMMAND;
unsigned IOCTL_ISCSI_REGISTER_EVENT = ISCSI_REGISTER_EVENT;
unsigned IOCTL_ISCSI_DEREGISTER_EVENT = ISCSI_DEREGISTER_EVENT;
unsigned IOCTL_ISCSI_WAIT_EVENT = ISCSI_WAIT_EVENT;
unsigned IOCTL_ISCSI_POLL_EVENT = ISCSI_POLL_EVENT;
unsigned IOCTL_OFIOCGET = OFIOCGET;
unsigned IOCTL_OFIOCSET = OFIOCSET;
unsigned IOCTL_OFIOCNEXTPROP = OFIOCNEXTPROP;
unsigned IOCTL_OFIOCGETOPTNODE = OFIOCGETOPTNODE;
unsigned IOCTL_OFIOCGETNEXT = OFIOCGETNEXT;
unsigned IOCTL_OFIOCGETCHILD = OFIOCGETCHILD;
unsigned IOCTL_OFIOCFINDDEVICE = OFIOCFINDDEVICE;
unsigned IOCTL_AMR_IO_VERSION = AMR_IO_VERSION;
unsigned IOCTL_AMR_IO_COMMAND = AMR_IO_COMMAND;
unsigned IOCTL_MLYIO_COMMAND = MLYIO_COMMAND;
unsigned IOCTL_MLYIO_HEALTH = MLYIO_HEALTH;
unsigned IOCTL_PCI_IOC_CFGREAD = PCI_IOC_CFGREAD;
unsigned IOCTL_PCI_IOC_CFGWRITE = PCI_IOC_CFGWRITE;
unsigned IOCTL_PCI_IOC_BDF_CFGREAD = PCI_IOC_BDF_CFGREAD;
unsigned IOCTL_PCI_IOC_BDF_CFGWRITE = PCI_IOC_BDF_CFGWRITE;
unsigned IOCTL_PCI_IOC_BUSINFO = PCI_IOC_BUSINFO;
unsigned IOCTL_PCI_IOC_DRVNAME = PCI_IOC_DRVNAME;
unsigned IOCTL_PCI_IOC_DRVNAMEONBUS = PCI_IOC_DRVNAMEONBUS;
unsigned IOCTL_TWEIO_COMMAND = TWEIO_COMMAND;
unsigned IOCTL_TWEIO_STATS = TWEIO_STATS;
unsigned IOCTL_TWEIO_AEN_POLL = TWEIO_AEN_POLL;
unsigned IOCTL_TWEIO_AEN_WAIT = TWEIO_AEN_WAIT;
unsigned IOCTL_TWEIO_SET_PARAM = TWEIO_SET_PARAM;
unsigned IOCTL_TWEIO_GET_PARAM = TWEIO_GET_PARAM;
unsigned IOCTL_TWEIO_RESET = TWEIO_RESET;
unsigned IOCTL_TWEIO_ADD_UNIT = TWEIO_ADD_UNIT;
unsigned IOCTL_TWEIO_DEL_UNIT = TWEIO_DEL_UNIT;
unsigned IOCTL_SIOCSCNWDOMAIN = SIOCSCNWDOMAIN;
unsigned IOCTL_SIOCGCNWDOMAIN = SIOCGCNWDOMAIN;
unsigned IOCTL_SIOCSCNWKEY = SIOCSCNWKEY;
unsigned IOCTL_SIOCGCNWSTATUS = SIOCGCNWSTATUS;
unsigned IOCTL_SIOCGCNWSTATS = SIOCGCNWSTATS;
unsigned IOCTL_SIOCGCNWTRAIL = SIOCGCNWTRAIL;
unsigned IOCTL_SIOCGRAYSIGLEV = SIOCGRAYSIGLEV;
unsigned IOCTL_RAIDFRAME_SHUTDOWN = RAIDFRAME_SHUTDOWN;
unsigned IOCTL_RAIDFRAME_TUR = RAIDFRAME_TUR;
unsigned IOCTL_RAIDFRAME_FAIL_DISK = RAIDFRAME_FAIL_DISK;
unsigned IOCTL_RAIDFRAME_CHECK_RECON_STATUS = RAIDFRAME_CHECK_RECON_STATUS;
unsigned IOCTL_RAIDFRAME_REWRITEPARITY = RAIDFRAME_REWRITEPARITY;
unsigned IOCTL_RAIDFRAME_COPYBACK = RAIDFRAME_COPYBACK;
unsigned IOCTL_RAIDFRAME_SPARET_WAIT = RAIDFRAME_SPARET_WAIT;
unsigned IOCTL_RAIDFRAME_SEND_SPARET = RAIDFRAME_SEND_SPARET;
unsigned IOCTL_RAIDFRAME_ABORT_SPARET_WAIT = RAIDFRAME_ABORT_SPARET_WAIT;
unsigned IOCTL_RAIDFRAME_START_ATRACE = RAIDFRAME_START_ATRACE;
unsigned IOCTL_RAIDFRAME_STOP_ATRACE = RAIDFRAME_STOP_ATRACE;
unsigned IOCTL_RAIDFRAME_GET_SIZE = RAIDFRAME_GET_SIZE;
unsigned IOCTL_RAIDFRAME_RESET_ACCTOTALS = RAIDFRAME_RESET_ACCTOTALS;
unsigned IOCTL_RAIDFRAME_KEEP_ACCTOTALS = RAIDFRAME_KEEP_ACCTOTALS;
unsigned IOCTL_RAIDFRAME_GET_COMPONENT_LABEL = RAIDFRAME_GET_COMPONENT_LABEL;
unsigned IOCTL_RAIDFRAME_SET_COMPONENT_LABEL = RAIDFRAME_SET_COMPONENT_LABEL;
unsigned IOCTL_RAIDFRAME_INIT_LABELS = RAIDFRAME_INIT_LABELS;
unsigned IOCTL_RAIDFRAME_ADD_HOT_SPARE = RAIDFRAME_ADD_HOT_SPARE;
unsigned IOCTL_RAIDFRAME_REMOVE_HOT_SPARE = RAIDFRAME_REMOVE_HOT_SPARE;
unsigned IOCTL_RAIDFRAME_REBUILD_IN_PLACE = RAIDFRAME_REBUILD_IN_PLACE;
unsigned IOCTL_RAIDFRAME_CHECK_PARITY = RAIDFRAME_CHECK_PARITY;
unsigned IOCTL_RAIDFRAME_CHECK_PARITYREWRITE_STATUS =
    RAIDFRAME_CHECK_PARITYREWRITE_STATUS;
unsigned IOCTL_RAIDFRAME_CHECK_COPYBACK_STATUS =
    RAIDFRAME_CHECK_COPYBACK_STATUS;
unsigned IOCTL_RAIDFRAME_SET_AUTOCONFIG = RAIDFRAME_SET_AUTOCONFIG;
unsigned IOCTL_RAIDFRAME_SET_ROOT = RAIDFRAME_SET_ROOT;
unsigned IOCTL_RAIDFRAME_DELETE_COMPONENT = RAIDFRAME_DELETE_COMPONENT;
unsigned IOCTL_RAIDFRAME_INCORPORATE_HOT_SPARE =
    RAIDFRAME_INCORPORATE_HOT_SPARE;
unsigned IOCTL_RAIDFRAME_CHECK_RECON_STATUS_EXT =
    RAIDFRAME_CHECK_RECON_STATUS_EXT;
unsigned IOCTL_RAIDFRAME_CHECK_PARITYREWRITE_STATUS_EXT =
    RAIDFRAME_CHECK_PARITYREWRITE_STATUS_EXT;
unsigned IOCTL_RAIDFRAME_CHECK_COPYBACK_STATUS_EXT =
    RAIDFRAME_CHECK_COPYBACK_STATUS_EXT;
unsigned IOCTL_RAIDFRAME_CONFIGURE = RAIDFRAME_CONFIGURE;
unsigned IOCTL_RAIDFRAME_GET_INFO = RAIDFRAME_GET_INFO;
unsigned IOCTL_RAIDFRAME_PARITYMAP_STATUS = RAIDFRAME_PARITYMAP_STATUS;
unsigned IOCTL_RAIDFRAME_PARITYMAP_GET_DISABLE =
    RAIDFRAME_PARITYMAP_GET_DISABLE;
unsigned IOCTL_RAIDFRAME_PARITYMAP_SET_DISABLE =
    RAIDFRAME_PARITYMAP_SET_DISABLE;
unsigned IOCTL_RAIDFRAME_PARITYMAP_SET_PARAMS = RAIDFRAME_PARITYMAP_SET_PARAMS;
unsigned IOCTL_RAIDFRAME_SET_LAST_UNIT = RAIDFRAME_SET_LAST_UNIT;
unsigned IOCTL_MBPPIOCSPARAM = MBPPIOCSPARAM;
unsigned IOCTL_MBPPIOCGPARAM = MBPPIOCGPARAM;
unsigned IOCTL_MBPPIOCGSTAT = MBPPIOCGSTAT;
unsigned IOCTL_SESIOC_GETNOBJ = SESIOC_GETNOBJ;
unsigned IOCTL_SESIOC_GETOBJMAP = SESIOC_GETOBJMAP;
unsigned IOCTL_SESIOC_GETENCSTAT = SESIOC_GETENCSTAT;
unsigned IOCTL_SESIOC_SETENCSTAT = SESIOC_SETENCSTAT;
unsigned IOCTL_SESIOC_GETOBJSTAT = SESIOC_GETOBJSTAT;
unsigned IOCTL_SESIOC_SETOBJSTAT = SESIOC_SETOBJSTAT;
unsigned IOCTL_SESIOC_GETTEXT = SESIOC_GETTEXT;
unsigned IOCTL_SESIOC_INIT = SESIOC_INIT;
unsigned IOCTL_SUN_DKIOCGGEOM = SUN_DKIOCGGEOM;
unsigned IOCTL_SUN_DKIOCINFO = SUN_DKIOCINFO;
unsigned IOCTL_SUN_DKIOCGPART = SUN_DKIOCGPART;
unsigned IOCTL_FBIOGTYPE = FBIOGTYPE;
unsigned IOCTL_FBIOPUTCMAP = FBIOPUTCMAP;
unsigned IOCTL_FBIOGETCMAP = FBIOGETCMAP;
unsigned IOCTL_FBIOGATTR = FBIOGATTR;
unsigned IOCTL_FBIOSVIDEO = FBIOSVIDEO;
unsigned IOCTL_FBIOGVIDEO = FBIOGVIDEO;
unsigned IOCTL_FBIOSCURSOR = FBIOSCURSOR;
unsigned IOCTL_FBIOGCURSOR = FBIOGCURSOR;
unsigned IOCTL_FBIOSCURPOS = FBIOSCURPOS;
unsigned IOCTL_FBIOGCURPOS = FBIOGCURPOS;
unsigned IOCTL_FBIOGCURMAX = FBIOGCURMAX;
unsigned IOCTL_KIOCTRANS = KIOCTRANS;
unsigned IOCTL_KIOCSETKEY = KIOCSETKEY;
unsigned IOCTL_KIOCGETKEY = KIOCGETKEY;
unsigned IOCTL_KIOCGTRANS = KIOCGTRANS;
unsigned IOCTL_KIOCCMD = KIOCCMD;
unsigned IOCTL_KIOCTYPE = KIOCTYPE;
unsigned IOCTL_KIOCSDIRECT = KIOCSDIRECT;
unsigned IOCTL_KIOCSKEY = KIOCSKEY;
unsigned IOCTL_KIOCGKEY = KIOCGKEY;
unsigned IOCTL_KIOCSLED = KIOCSLED;
unsigned IOCTL_KIOCGLED = KIOCGLED;
unsigned IOCTL_KIOCLAYOUT = KIOCLAYOUT;
unsigned IOCTL_VUIDSFORMAT = VUIDSFORMAT;
unsigned IOCTL_VUIDGFORMAT = VUIDGFORMAT;
unsigned IOCTL_STICIO_GXINFO = STICIO_GXINFO;
unsigned IOCTL_STICIO_RESET = STICIO_RESET;
unsigned IOCTL_STICIO_STARTQ = STICIO_STARTQ;
unsigned IOCTL_STICIO_STOPQ = STICIO_STOPQ;
unsigned IOCTL_UKYOPON_IDENTIFY = UKYOPON_IDENTIFY;
unsigned IOCTL_URIO_SEND_COMMAND = URIO_SEND_COMMAND;
unsigned IOCTL_URIO_RECV_COMMAND = URIO_RECV_COMMAND;
unsigned IOCTL_USB_REQUEST = USB_REQUEST;
unsigned IOCTL_USB_SETDEBUG = USB_SETDEBUG;
unsigned IOCTL_USB_DISCOVER = USB_DISCOVER;
unsigned IOCTL_USB_DEVICEINFO = USB_DEVICEINFO;
unsigned IOCTL_USB_DEVICEINFO_OLD = USB_DEVICEINFO_OLD;
unsigned IOCTL_USB_DEVICESTATS = USB_DEVICESTATS;
unsigned IOCTL_USB_GET_REPORT_DESC = USB_GET_REPORT_DESC;
unsigned IOCTL_USB_SET_IMMED = USB_SET_IMMED;
unsigned IOCTL_USB_GET_REPORT = USB_GET_REPORT;
unsigned IOCTL_USB_SET_REPORT = USB_SET_REPORT;
unsigned IOCTL_USB_GET_REPORT_ID = USB_GET_REPORT_ID;
unsigned IOCTL_USB_GET_CONFIG = USB_GET_CONFIG;
unsigned IOCTL_USB_SET_CONFIG = USB_SET_CONFIG;
unsigned IOCTL_USB_GET_ALTINTERFACE = USB_GET_ALTINTERFACE;
unsigned IOCTL_USB_SET_ALTINTERFACE = USB_SET_ALTINTERFACE;
unsigned IOCTL_USB_GET_NO_ALT = USB_GET_NO_ALT;
unsigned IOCTL_USB_GET_DEVICE_DESC = USB_GET_DEVICE_DESC;
unsigned IOCTL_USB_GET_CONFIG_DESC = USB_GET_CONFIG_DESC;
unsigned IOCTL_USB_GET_INTERFACE_DESC = USB_GET_INTERFACE_DESC;
unsigned IOCTL_USB_GET_ENDPOINT_DESC = USB_GET_ENDPOINT_DESC;
unsigned IOCTL_USB_GET_FULL_DESC = USB_GET_FULL_DESC;
unsigned IOCTL_USB_GET_STRING_DESC = USB_GET_STRING_DESC;
unsigned IOCTL_USB_DO_REQUEST = USB_DO_REQUEST;
unsigned IOCTL_USB_GET_DEVICEINFO = USB_GET_DEVICEINFO;
unsigned IOCTL_USB_GET_DEVICEINFO_OLD = USB_GET_DEVICEINFO_OLD;
unsigned IOCTL_USB_SET_SHORT_XFER = USB_SET_SHORT_XFER;
unsigned IOCTL_USB_SET_TIMEOUT = USB_SET_TIMEOUT;
unsigned IOCTL_USB_SET_BULK_RA = USB_SET_BULK_RA;
unsigned IOCTL_USB_SET_BULK_WB = USB_SET_BULK_WB;
unsigned IOCTL_USB_SET_BULK_RA_OPT = USB_SET_BULK_RA_OPT;
unsigned IOCTL_USB_SET_BULK_WB_OPT = USB_SET_BULK_WB_OPT;
unsigned IOCTL_USB_GET_CM_OVER_DATA = USB_GET_CM_OVER_DATA;
unsigned IOCTL_USB_SET_CM_OVER_DATA = USB_SET_CM_OVER_DATA;
unsigned IOCTL_UTOPPYIOTURBO = UTOPPYIOTURBO;
unsigned IOCTL_UTOPPYIOCANCEL = UTOPPYIOCANCEL;
unsigned IOCTL_UTOPPYIOREBOOT = UTOPPYIOREBOOT;
unsigned IOCTL_UTOPPYIOSTATS = UTOPPYIOSTATS;
unsigned IOCTL_UTOPPYIORENAME = UTOPPYIORENAME;
unsigned IOCTL_UTOPPYIOMKDIR = UTOPPYIOMKDIR;
unsigned IOCTL_UTOPPYIODELETE = UTOPPYIODELETE;
unsigned IOCTL_UTOPPYIOREADDIR = UTOPPYIOREADDIR;
unsigned IOCTL_UTOPPYIOREADFILE = UTOPPYIOREADFILE;
unsigned IOCTL_UTOPPYIOWRITEFILE = UTOPPYIOWRITEFILE;
unsigned IOCTL_DIOSXDCMD = DIOSXDCMD;
unsigned IOCTL_VT_OPENQRY = VT_OPENQRY;
unsigned IOCTL_VT_SETMODE = VT_SETMODE;
unsigned IOCTL_VT_GETMODE = VT_GETMODE;
unsigned IOCTL_VT_RELDISP = VT_RELDISP;
unsigned IOCTL_VT_ACTIVATE = VT_ACTIVATE;
unsigned IOCTL_VT_WAITACTIVE = VT_WAITACTIVE;
unsigned IOCTL_VT_GETACTIVE = VT_GETACTIVE;
unsigned IOCTL_VT_GETSTATE = VT_GETSTATE;
unsigned IOCTL_KDGETKBENT = KDGETKBENT;
unsigned IOCTL_KDGKBMODE = KDGKBMODE;
unsigned IOCTL_KDSKBMODE = KDSKBMODE;
unsigned IOCTL_KDMKTONE = KDMKTONE;
unsigned IOCTL_KDSETMODE = KDSETMODE;
unsigned IOCTL_KDENABIO = KDENABIO;
unsigned IOCTL_KDDISABIO = KDDISABIO;
unsigned IOCTL_KDGKBTYPE = KDGKBTYPE;
unsigned IOCTL_KDGETLED = KDGETLED;
unsigned IOCTL_KDSETLED = KDSETLED;
unsigned IOCTL_KDSETRAD = KDSETRAD;
unsigned IOCTL_VGAPCVTID = VGAPCVTID;
unsigned IOCTL_CONS_GETVERS = CONS_GETVERS;
unsigned IOCTL_WSKBDIO_GTYPE = WSKBDIO_GTYPE;
unsigned IOCTL_WSKBDIO_BELL = WSKBDIO_BELL;
unsigned IOCTL_WSKBDIO_COMPLEXBELL = WSKBDIO_COMPLEXBELL;
unsigned IOCTL_WSKBDIO_SETBELL = WSKBDIO_SETBELL;
unsigned IOCTL_WSKBDIO_GETBELL = WSKBDIO_GETBELL;
unsigned IOCTL_WSKBDIO_SETDEFAULTBELL = WSKBDIO_SETDEFAULTBELL;
unsigned IOCTL_WSKBDIO_GETDEFAULTBELL = WSKBDIO_GETDEFAULTBELL;
unsigned IOCTL_WSKBDIO_SETKEYREPEAT = WSKBDIO_SETKEYREPEAT;
unsigned IOCTL_WSKBDIO_GETKEYREPEAT = WSKBDIO_GETKEYREPEAT;
unsigned IOCTL_WSKBDIO_SETDEFAULTKEYREPEAT = WSKBDIO_SETDEFAULTKEYREPEAT;
unsigned IOCTL_WSKBDIO_GETDEFAULTKEYREPEAT = WSKBDIO_GETDEFAULTKEYREPEAT;
unsigned IOCTL_WSKBDIO_SETLEDS = WSKBDIO_SETLEDS;
unsigned IOCTL_WSKBDIO_GETLEDS = WSKBDIO_GETLEDS;
unsigned IOCTL_WSKBDIO_GETMAP = WSKBDIO_GETMAP;
unsigned IOCTL_WSKBDIO_SETMAP = WSKBDIO_SETMAP;
unsigned IOCTL_WSKBDIO_GETENCODING = WSKBDIO_GETENCODING;
unsigned IOCTL_WSKBDIO_SETENCODING = WSKBDIO_SETENCODING;
unsigned IOCTL_WSKBDIO_SETMODE = WSKBDIO_SETMODE;
unsigned IOCTL_WSKBDIO_GETMODE = WSKBDIO_GETMODE;
unsigned IOCTL_WSKBDIO_SETKEYCLICK = WSKBDIO_SETKEYCLICK;
unsigned IOCTL_WSKBDIO_GETKEYCLICK = WSKBDIO_GETKEYCLICK;
unsigned IOCTL_WSKBDIO_GETSCROLL = WSKBDIO_GETSCROLL;
unsigned IOCTL_WSKBDIO_SETSCROLL = WSKBDIO_SETSCROLL;
unsigned IOCTL_WSKBDIO_SETVERSION = WSKBDIO_SETVERSION;
unsigned IOCTL_WSMOUSEIO_GTYPE = WSMOUSEIO_GTYPE;
unsigned IOCTL_WSMOUSEIO_SRES = WSMOUSEIO_SRES;
unsigned IOCTL_WSMOUSEIO_SSCALE = WSMOUSEIO_SSCALE;
unsigned IOCTL_WSMOUSEIO_SRATE = WSMOUSEIO_SRATE;
unsigned IOCTL_WSMOUSEIO_SCALIBCOORDS = WSMOUSEIO_SCALIBCOORDS;
unsigned IOCTL_WSMOUSEIO_GCALIBCOORDS = WSMOUSEIO_GCALIBCOORDS;
unsigned IOCTL_WSMOUSEIO_GETID = WSMOUSEIO_GETID;
unsigned IOCTL_WSMOUSEIO_GETREPEAT = WSMOUSEIO_GETREPEAT;
unsigned IOCTL_WSMOUSEIO_SETREPEAT = WSMOUSEIO_SETREPEAT;
unsigned IOCTL_WSMOUSEIO_SETVERSION = WSMOUSEIO_SETVERSION;
unsigned IOCTL_WSDISPLAYIO_GTYPE = WSDISPLAYIO_GTYPE;
unsigned IOCTL_WSDISPLAYIO_GINFO = WSDISPLAYIO_GINFO;
unsigned IOCTL_WSDISPLAYIO_GETCMAP = WSDISPLAYIO_GETCMAP;
unsigned IOCTL_WSDISPLAYIO_PUTCMAP = WSDISPLAYIO_PUTCMAP;
unsigned IOCTL_WSDISPLAYIO_GVIDEO = WSDISPLAYIO_GVIDEO;
unsigned IOCTL_WSDISPLAYIO_SVIDEO = WSDISPLAYIO_SVIDEO;
unsigned IOCTL_WSDISPLAYIO_GCURPOS = WSDISPLAYIO_GCURPOS;
unsigned IOCTL_WSDISPLAYIO_SCURPOS = WSDISPLAYIO_SCURPOS;
unsigned IOCTL_WSDISPLAYIO_GCURMAX = WSDISPLAYIO_GCURMAX;
unsigned IOCTL_WSDISPLAYIO_GCURSOR = WSDISPLAYIO_GCURSOR;
unsigned IOCTL_WSDISPLAYIO_SCURSOR = WSDISPLAYIO_SCURSOR;
unsigned IOCTL_WSDISPLAYIO_GMODE = WSDISPLAYIO_GMODE;
unsigned IOCTL_WSDISPLAYIO_SMODE = WSDISPLAYIO_SMODE;
unsigned IOCTL_WSDISPLAYIO_LDFONT = WSDISPLAYIO_LDFONT;
unsigned IOCTL_WSDISPLAYIO_ADDSCREEN = WSDISPLAYIO_ADDSCREEN;
unsigned IOCTL_WSDISPLAYIO_DELSCREEN = WSDISPLAYIO_DELSCREEN;
unsigned IOCTL_WSDISPLAYIO_SFONT = WSDISPLAYIO_SFONT;
unsigned IOCTL__O_WSDISPLAYIO_SETKEYBOARD = _O_WSDISPLAYIO_SETKEYBOARD;
unsigned IOCTL_WSDISPLAYIO_GETPARAM = WSDISPLAYIO_GETPARAM;
unsigned IOCTL_WSDISPLAYIO_SETPARAM = WSDISPLAYIO_SETPARAM;
unsigned IOCTL_WSDISPLAYIO_GETACTIVESCREEN = WSDISPLAYIO_GETACTIVESCREEN;
unsigned IOCTL_WSDISPLAYIO_GETWSCHAR = WSDISPLAYIO_GETWSCHAR;
unsigned IOCTL_WSDISPLAYIO_PUTWSCHAR = WSDISPLAYIO_PUTWSCHAR;
unsigned IOCTL_WSDISPLAYIO_DGSCROLL = WSDISPLAYIO_DGSCROLL;
unsigned IOCTL_WSDISPLAYIO_DSSCROLL = WSDISPLAYIO_DSSCROLL;
unsigned IOCTL_WSDISPLAYIO_GMSGATTRS = WSDISPLAYIO_GMSGATTRS;
unsigned IOCTL_WSDISPLAYIO_SMSGATTRS = WSDISPLAYIO_SMSGATTRS;
unsigned IOCTL_WSDISPLAYIO_GBORDER = WSDISPLAYIO_GBORDER;
unsigned IOCTL_WSDISPLAYIO_SBORDER = WSDISPLAYIO_SBORDER;
unsigned IOCTL_WSDISPLAYIO_SSPLASH = WSDISPLAYIO_SSPLASH;
unsigned IOCTL_WSDISPLAYIO_SPROGRESS = WSDISPLAYIO_SPROGRESS;
unsigned IOCTL_WSDISPLAYIO_LINEBYTES = WSDISPLAYIO_LINEBYTES;
unsigned IOCTL_WSDISPLAYIO_SETVERSION = WSDISPLAYIO_SETVERSION;
unsigned IOCTL_WSMUXIO_ADD_DEVICE = WSMUXIO_ADD_DEVICE;
unsigned IOCTL_WSMUXIO_REMOVE_DEVICE = WSMUXIO_REMOVE_DEVICE;
unsigned IOCTL_WSMUXIO_LIST_DEVICES = WSMUXIO_LIST_DEVICES;
unsigned IOCTL_WSMUXIO_INJECTEVENT = WSMUXIO_INJECTEVENT;
unsigned IOCTL_WSDISPLAYIO_GET_BUSID = WSDISPLAYIO_GET_BUSID;
unsigned IOCTL_WSDISPLAYIO_GET_EDID = WSDISPLAYIO_GET_EDID;
unsigned IOCTL_WSDISPLAYIO_SET_POLLING = WSDISPLAYIO_SET_POLLING;
unsigned IOCTL_WSDISPLAYIO_GET_FBINFO = WSDISPLAYIO_GET_FBINFO;
unsigned IOCTL_WSDISPLAYIO_DOBLIT = WSDISPLAYIO_DOBLIT;
unsigned IOCTL_WSDISPLAYIO_WAITBLIT = WSDISPLAYIO_WAITBLIT;
unsigned IOCTL_BIOCLOCATE = BIOCLOCATE;
unsigned IOCTL_BIOCINQ = BIOCINQ;
unsigned IOCTL_BIOCDISK_NOVOL = BIOCDISK_NOVOL;
unsigned IOCTL_BIOCDISK = BIOCDISK;
unsigned IOCTL_BIOCVOL = BIOCVOL;
unsigned IOCTL_BIOCALARM = BIOCALARM;
unsigned IOCTL_BIOCBLINK = BIOCBLINK;
unsigned IOCTL_BIOCSETSTATE = BIOCSETSTATE;
unsigned IOCTL_BIOCVOLOPS = BIOCVOLOPS;
unsigned IOCTL_MD_GETCONF = MD_GETCONF;
unsigned IOCTL_MD_SETCONF = MD_SETCONF;
unsigned IOCTL_CCDIOCSET = CCDIOCSET;
unsigned IOCTL_CCDIOCCLR = CCDIOCCLR;
unsigned IOCTL_CGDIOCSET = CGDIOCSET;
unsigned IOCTL_CGDIOCCLR = CGDIOCCLR;
unsigned IOCTL_CGDIOCGET = CGDIOCGET;
unsigned IOCTL_FSSIOCSET = FSSIOCSET;
unsigned IOCTL_FSSIOCGET = FSSIOCGET;
unsigned IOCTL_FSSIOCCLR = FSSIOCCLR;
unsigned IOCTL_FSSIOFSET = FSSIOFSET;
unsigned IOCTL_FSSIOFGET = FSSIOFGET;
unsigned IOCTL_BTDEV_ATTACH = BTDEV_ATTACH;
unsigned IOCTL_BTDEV_DETACH = BTDEV_DETACH;
unsigned IOCTL_BTSCO_GETINFO = BTSCO_GETINFO;
unsigned IOCTL_KTTCP_IO_SEND = KTTCP_IO_SEND;
unsigned IOCTL_KTTCP_IO_RECV = KTTCP_IO_RECV;
unsigned IOCTL_IOC_LOCKSTAT_GVERSION = IOC_LOCKSTAT_GVERSION;
unsigned IOCTL_IOC_LOCKSTAT_ENABLE = IOC_LOCKSTAT_ENABLE;
unsigned IOCTL_IOC_LOCKSTAT_DISABLE = IOC_LOCKSTAT_DISABLE;
unsigned IOCTL_VNDIOCSET = VNDIOCSET;
unsigned IOCTL_VNDIOCCLR = VNDIOCCLR;
unsigned IOCTL_VNDIOCGET = VNDIOCGET;
unsigned IOCTL_SPKRTONE = SPKRTONE;
unsigned IOCTL_SPKRTUNE = SPKRTUNE;
unsigned IOCTL_SPKRGETVOL = SPKRGETVOL;
unsigned IOCTL_SPKRSETVOL = SPKRSETVOL;
unsigned IOCTL_BIOCGBLEN = BIOCGBLEN;
unsigned IOCTL_BIOCSBLEN = BIOCSBLEN;
unsigned IOCTL_BIOCSETF = BIOCSETF;
unsigned IOCTL_BIOCFLUSH = BIOCFLUSH;
unsigned IOCTL_BIOCPROMISC = BIOCPROMISC;
unsigned IOCTL_BIOCGDLT = BIOCGDLT;
unsigned IOCTL_BIOCGETIF = BIOCGETIF;
unsigned IOCTL_BIOCSETIF = BIOCSETIF;
unsigned IOCTL_BIOCGSTATS = BIOCGSTATS;
unsigned IOCTL_BIOCGSTATSOLD = BIOCGSTATSOLD;
unsigned IOCTL_BIOCIMMEDIATE = BIOCIMMEDIATE;
unsigned IOCTL_BIOCVERSION = BIOCVERSION;
unsigned IOCTL_BIOCSTCPF = BIOCSTCPF;
unsigned IOCTL_BIOCSUDPF = BIOCSUDPF;
unsigned IOCTL_BIOCGHDRCMPLT = BIOCGHDRCMPLT;
unsigned IOCTL_BIOCSHDRCMPLT = BIOCSHDRCMPLT;
unsigned IOCTL_BIOCSDLT = BIOCSDLT;
unsigned IOCTL_BIOCGDLTLIST = BIOCGDLTLIST;
unsigned IOCTL_BIOCGSEESENT = BIOCGSEESENT;
unsigned IOCTL_BIOCSSEESENT = BIOCSSEESENT;
unsigned IOCTL_BIOCSRTIMEOUT = BIOCSRTIMEOUT;
unsigned IOCTL_BIOCGRTIMEOUT = BIOCGRTIMEOUT;
unsigned IOCTL_BIOCGFEEDBACK = BIOCGFEEDBACK;
unsigned IOCTL_BIOCSFEEDBACK = BIOCSFEEDBACK;
unsigned IOCTL_SIOCRAWATM = SIOCRAWATM;
unsigned IOCTL_SIOCATMENA = SIOCATMENA;
unsigned IOCTL_SIOCATMDIS = SIOCATMDIS;
unsigned IOCTL_SIOCSPVCTX = SIOCSPVCTX;
unsigned IOCTL_SIOCGPVCTX = SIOCGPVCTX;
unsigned IOCTL_SIOCSPVCSIF = SIOCSPVCSIF;
unsigned IOCTL_SIOCGPVCSIF = SIOCGPVCSIF;
unsigned IOCTL_GRESADDRS = GRESADDRS;
unsigned IOCTL_GRESADDRD = GRESADDRD;
unsigned IOCTL_GREGADDRS = GREGADDRS;
unsigned IOCTL_GREGADDRD = GREGADDRD;
unsigned IOCTL_GRESPROTO = GRESPROTO;
unsigned IOCTL_GREGPROTO = GREGPROTO;
unsigned IOCTL_GRESSOCK = GRESSOCK;
unsigned IOCTL_GREDSOCK = GREDSOCK;
unsigned IOCTL_PPPIOCGRAWIN = PPPIOCGRAWIN;
unsigned IOCTL_PPPIOCGFLAGS = PPPIOCGFLAGS;
unsigned IOCTL_PPPIOCSFLAGS = PPPIOCSFLAGS;
unsigned IOCTL_PPPIOCGASYNCMAP = PPPIOCGASYNCMAP;
unsigned IOCTL_PPPIOCSASYNCMAP = PPPIOCSASYNCMAP;
unsigned IOCTL_PPPIOCGUNIT = PPPIOCGUNIT;
unsigned IOCTL_PPPIOCGRASYNCMAP = PPPIOCGRASYNCMAP;
unsigned IOCTL_PPPIOCSRASYNCMAP = PPPIOCSRASYNCMAP;
unsigned IOCTL_PPPIOCGMRU = PPPIOCGMRU;
unsigned IOCTL_PPPIOCSMRU = PPPIOCSMRU;
unsigned IOCTL_PPPIOCSMAXCID = PPPIOCSMAXCID;
unsigned IOCTL_PPPIOCGXASYNCMAP = PPPIOCGXASYNCMAP;
unsigned IOCTL_PPPIOCSXASYNCMAP = PPPIOCSXASYNCMAP;
unsigned IOCTL_PPPIOCXFERUNIT = PPPIOCXFERUNIT;
unsigned IOCTL_PPPIOCSCOMPRESS = PPPIOCSCOMPRESS;
unsigned IOCTL_PPPIOCGNPMODE = PPPIOCGNPMODE;
unsigned IOCTL_PPPIOCSNPMODE = PPPIOCSNPMODE;
unsigned IOCTL_PPPIOCGIDLE = PPPIOCGIDLE;
unsigned IOCTL_PPPIOCGMTU = PPPIOCGMTU;
unsigned IOCTL_PPPIOCSMTU = PPPIOCSMTU;
unsigned IOCTL_SIOCGPPPSTATS = SIOCGPPPSTATS;
unsigned IOCTL_SIOCGPPPCSTATS = SIOCGPPPCSTATS;
unsigned IOCTL_IOC_NPF_VERSION = IOC_NPF_VERSION;
unsigned IOCTL_IOC_NPF_SWITCH = IOC_NPF_SWITCH;
unsigned IOCTL_IOC_NPF_LOAD = IOC_NPF_LOAD;
unsigned IOCTL_IOC_NPF_TABLE = IOC_NPF_TABLE;
unsigned IOCTL_IOC_NPF_STATS = IOC_NPF_STATS;
unsigned IOCTL_IOC_NPF_SAVE = IOC_NPF_SAVE;
unsigned IOCTL_IOC_NPF_RULE = IOC_NPF_RULE;
unsigned IOCTL_IOC_NPF_CONN_LOOKUP = IOC_NPF_CONN_LOOKUP;
unsigned IOCTL_PPPOESETPARMS = PPPOESETPARMS;
unsigned IOCTL_PPPOEGETPARMS = PPPOEGETPARMS;
unsigned IOCTL_PPPOEGETSESSION = PPPOEGETSESSION;
unsigned IOCTL_SPPPGETAUTHCFG = SPPPGETAUTHCFG;
unsigned IOCTL_SPPPSETAUTHCFG = SPPPSETAUTHCFG;
unsigned IOCTL_SPPPGETLCPCFG = SPPPGETLCPCFG;
unsigned IOCTL_SPPPSETLCPCFG = SPPPSETLCPCFG;
unsigned IOCTL_SPPPGETSTATUS = SPPPGETSTATUS;
unsigned IOCTL_SPPPGETSTATUSNCP = SPPPGETSTATUSNCP;
unsigned IOCTL_SPPPGETIDLETO = SPPPGETIDLETO;
unsigned IOCTL_SPPPSETIDLETO = SPPPSETIDLETO;
unsigned IOCTL_SPPPGETAUTHFAILURES = SPPPGETAUTHFAILURES;
unsigned IOCTL_SPPPSETAUTHFAILURE = SPPPSETAUTHFAILURE;
unsigned IOCTL_SPPPSETDNSOPTS = SPPPSETDNSOPTS;
unsigned IOCTL_SPPPGETDNSOPTS = SPPPGETDNSOPTS;
unsigned IOCTL_SPPPGETDNSADDRS = SPPPGETDNSADDRS;
unsigned IOCTL_SPPPSETKEEPALIVE = SPPPSETKEEPALIVE;
unsigned IOCTL_SPPPGETKEEPALIVE = SPPPGETKEEPALIVE;
unsigned IOCTL_SRT_GETNRT = SRT_GETNRT;
unsigned IOCTL_SRT_GETRT = SRT_GETRT;
unsigned IOCTL_SRT_SETRT = SRT_SETRT;
unsigned IOCTL_SRT_DELRT = SRT_DELRT;
unsigned IOCTL_SRT_SFLAGS = SRT_SFLAGS;
unsigned IOCTL_SRT_GFLAGS = SRT_GFLAGS;
unsigned IOCTL_SRT_SGFLAGS = SRT_SGFLAGS;
unsigned IOCTL_SRT_DEBUG = SRT_DEBUG;
unsigned IOCTL_TAPGIFNAME = TAPGIFNAME;
unsigned IOCTL_TUNSDEBUG = TUNSDEBUG;
unsigned IOCTL_TUNGDEBUG = TUNGDEBUG;
unsigned IOCTL_TUNSIFMODE = TUNSIFMODE;
unsigned IOCTL_TUNSLMODE = TUNSLMODE;
unsigned IOCTL_TUNSIFHEAD = TUNSIFHEAD;
unsigned IOCTL_TUNGIFHEAD = TUNGIFHEAD;
unsigned IOCTL_DIOCSTART = DIOCSTART;
unsigned IOCTL_DIOCSTOP = DIOCSTOP;
unsigned IOCTL_DIOCADDRULE = DIOCADDRULE;
unsigned IOCTL_DIOCGETRULES = DIOCGETRULES;
unsigned IOCTL_DIOCGETRULE = DIOCGETRULE;
unsigned IOCTL_DIOCSETLCK = DIOCSETLCK;
unsigned IOCTL_DIOCCLRSTATES = DIOCCLRSTATES;
unsigned IOCTL_DIOCGETSTATE = DIOCGETSTATE;
unsigned IOCTL_DIOCSETSTATUSIF = DIOCSETSTATUSIF;
unsigned IOCTL_DIOCGETSTATUS = DIOCGETSTATUS;
unsigned IOCTL_DIOCCLRSTATUS = DIOCCLRSTATUS;
unsigned IOCTL_DIOCNATLOOK = DIOCNATLOOK;
unsigned IOCTL_DIOCSETDEBUG = DIOCSETDEBUG;
unsigned IOCTL_DIOCGETSTATES = DIOCGETSTATES;
unsigned IOCTL_DIOCCHANGERULE = DIOCCHANGERULE;
unsigned IOCTL_DIOCSETTIMEOUT = DIOCSETTIMEOUT;
unsigned IOCTL_DIOCGETTIMEOUT = DIOCGETTIMEOUT;
unsigned IOCTL_DIOCADDSTATE = DIOCADDSTATE;
unsigned IOCTL_DIOCCLRRULECTRS = DIOCCLRRULECTRS;
unsigned IOCTL_DIOCGETLIMIT = DIOCGETLIMIT;
unsigned IOCTL_DIOCSETLIMIT = DIOCSETLIMIT;
unsigned IOCTL_DIOCKILLSTATES = DIOCKILLSTATES;
unsigned IOCTL_DIOCSTARTALTQ = DIOCSTARTALTQ;
unsigned IOCTL_DIOCSTOPALTQ = DIOCSTOPALTQ;
unsigned IOCTL_DIOCADDALTQ = DIOCADDALTQ;
unsigned IOCTL_DIOCGETALTQS = DIOCGETALTQS;
unsigned IOCTL_DIOCGETALTQ = DIOCGETALTQ;
unsigned IOCTL_DIOCCHANGEALTQ = DIOCCHANGEALTQ;
unsigned IOCTL_DIOCGETQSTATS = DIOCGETQSTATS;
unsigned IOCTL_DIOCBEGINADDRS = DIOCBEGINADDRS;
unsigned IOCTL_DIOCADDADDR = DIOCADDADDR;
unsigned IOCTL_DIOCGETADDRS = DIOCGETADDRS;
unsigned IOCTL_DIOCGETADDR = DIOCGETADDR;
unsigned IOCTL_DIOCCHANGEADDR = DIOCCHANGEADDR;
unsigned IOCTL_DIOCADDSTATES = DIOCADDSTATES;
unsigned IOCTL_DIOCGETRULESETS = DIOCGETRULESETS;
unsigned IOCTL_DIOCGETRULESET = DIOCGETRULESET;
unsigned IOCTL_DIOCRCLRTABLES = DIOCRCLRTABLES;
unsigned IOCTL_DIOCRADDTABLES = DIOCRADDTABLES;
unsigned IOCTL_DIOCRDELTABLES = DIOCRDELTABLES;
unsigned IOCTL_DIOCRGETTABLES = DIOCRGETTABLES;
unsigned IOCTL_DIOCRGETTSTATS = DIOCRGETTSTATS;
unsigned IOCTL_DIOCRCLRTSTATS = DIOCRCLRTSTATS;
unsigned IOCTL_DIOCRCLRADDRS = DIOCRCLRADDRS;
unsigned IOCTL_DIOCRADDADDRS = DIOCRADDADDRS;
unsigned IOCTL_DIOCRDELADDRS = DIOCRDELADDRS;
unsigned IOCTL_DIOCRSETADDRS = DIOCRSETADDRS;
unsigned IOCTL_DIOCRGETADDRS = DIOCRGETADDRS;
unsigned IOCTL_DIOCRGETASTATS = DIOCRGETASTATS;
unsigned IOCTL_DIOCRCLRASTATS = DIOCRCLRASTATS;
unsigned IOCTL_DIOCRTSTADDRS = DIOCRTSTADDRS;
unsigned IOCTL_DIOCRSETTFLAGS = DIOCRSETTFLAGS;
unsigned IOCTL_DIOCRINADEFINE = DIOCRINADEFINE;
unsigned IOCTL_DIOCOSFPFLUSH = DIOCOSFPFLUSH;
unsigned IOCTL_DIOCOSFPADD = DIOCOSFPADD;
unsigned IOCTL_DIOCOSFPGET = DIOCOSFPGET;
unsigned IOCTL_DIOCXBEGIN = DIOCXBEGIN;
unsigned IOCTL_DIOCXCOMMIT = DIOCXCOMMIT;
unsigned IOCTL_DIOCXROLLBACK = DIOCXROLLBACK;
unsigned IOCTL_DIOCGETSRCNODES = DIOCGETSRCNODES;
unsigned IOCTL_DIOCCLRSRCNODES = DIOCCLRSRCNODES;
unsigned IOCTL_DIOCSETHOSTID = DIOCSETHOSTID;
unsigned IOCTL_DIOCIGETIFACES = DIOCIGETIFACES;
unsigned IOCTL_DIOCSETIFFLAG = DIOCSETIFFLAG;
unsigned IOCTL_DIOCCLRIFFLAG = DIOCCLRIFFLAG;
unsigned IOCTL_DIOCKILLSRCNODES = DIOCKILLSRCNODES;
unsigned IOCTL_SLIOCGUNIT = SLIOCGUNIT;
unsigned IOCTL_SIOCGBTINFO = SIOCGBTINFO;
unsigned IOCTL_SIOCGBTINFOA = SIOCGBTINFOA;
unsigned IOCTL_SIOCNBTINFO = SIOCNBTINFO;
unsigned IOCTL_SIOCSBTFLAGS = SIOCSBTFLAGS;
unsigned IOCTL_SIOCSBTPOLICY = SIOCSBTPOLICY;
unsigned IOCTL_SIOCSBTPTYPE = SIOCSBTPTYPE;
unsigned IOCTL_SIOCGBTSTATS = SIOCGBTSTATS;
unsigned IOCTL_SIOCZBTSTATS = SIOCZBTSTATS;
unsigned IOCTL_SIOCBTDUMP = SIOCBTDUMP;
unsigned IOCTL_SIOCSBTSCOMTU = SIOCSBTSCOMTU;
unsigned IOCTL_SIOCGBTFEAT = SIOCGBTFEAT;
unsigned IOCTL_SIOCADNAT = SIOCADNAT;
unsigned IOCTL_SIOCRMNAT = SIOCRMNAT;
unsigned IOCTL_SIOCGNATS = SIOCGNATS;
unsigned IOCTL_SIOCGNATL = SIOCGNATL;
unsigned IOCTL_SIOCPURGENAT = SIOCPURGENAT;
unsigned IOCTL_SIOCSIFINFO_FLAGS = SIOCSIFINFO_FLAGS;
unsigned IOCTL_SIOCAADDRCTL_POLICY = SIOCAADDRCTL_POLICY;
unsigned IOCTL_SIOCDADDRCTL_POLICY = SIOCDADDRCTL_POLICY;
unsigned IOCTL_SMBIOC_OPENSESSION = SMBIOC_OPENSESSION;
unsigned IOCTL_SMBIOC_OPENSHARE = SMBIOC_OPENSHARE;
unsigned IOCTL_SMBIOC_REQUEST = SMBIOC_REQUEST;
unsigned IOCTL_SMBIOC_SETFLAGS = SMBIOC_SETFLAGS;
unsigned IOCTL_SMBIOC_LOOKUP = SMBIOC_LOOKUP;
unsigned IOCTL_SMBIOC_READ = SMBIOC_READ;
unsigned IOCTL_SMBIOC_WRITE = SMBIOC_WRITE;
unsigned IOCTL_AGPIOC_INFO = AGPIOC_INFO;
unsigned IOCTL_AGPIOC_ACQUIRE = AGPIOC_ACQUIRE;
unsigned IOCTL_AGPIOC_RELEASE = AGPIOC_RELEASE;
unsigned IOCTL_AGPIOC_SETUP = AGPIOC_SETUP;
unsigned IOCTL_AGPIOC_ALLOCATE = AGPIOC_ALLOCATE;
unsigned IOCTL_AGPIOC_DEALLOCATE = AGPIOC_DEALLOCATE;
unsigned IOCTL_AGPIOC_BIND = AGPIOC_BIND;
unsigned IOCTL_AGPIOC_UNBIND = AGPIOC_UNBIND;
unsigned IOCTL_AUDIO_GETINFO = AUDIO_GETINFO;
unsigned IOCTL_AUDIO_SETINFO = AUDIO_SETINFO;
unsigned IOCTL_AUDIO_DRAIN = AUDIO_DRAIN;
unsigned IOCTL_AUDIO_FLUSH = AUDIO_FLUSH;
unsigned IOCTL_AUDIO_WSEEK = AUDIO_WSEEK;
unsigned IOCTL_AUDIO_RERROR = AUDIO_RERROR;
unsigned IOCTL_AUDIO_GETDEV = AUDIO_GETDEV;
unsigned IOCTL_AUDIO_GETENC = AUDIO_GETENC;
unsigned IOCTL_AUDIO_GETFD = AUDIO_GETFD;
unsigned IOCTL_AUDIO_SETFD = AUDIO_SETFD;
unsigned IOCTL_AUDIO_PERROR = AUDIO_PERROR;
unsigned IOCTL_AUDIO_GETIOFFS = AUDIO_GETIOFFS;
unsigned IOCTL_AUDIO_GETOOFFS = AUDIO_GETOOFFS;
unsigned IOCTL_AUDIO_GETPROPS = AUDIO_GETPROPS;
unsigned IOCTL_AUDIO_GETBUFINFO = AUDIO_GETBUFINFO;
unsigned IOCTL_AUDIO_SETCHAN = AUDIO_SETCHAN;
unsigned IOCTL_AUDIO_GETCHAN = AUDIO_GETCHAN;
unsigned IOCTL_AUDIO_MIXER_READ = AUDIO_MIXER_READ;
unsigned IOCTL_AUDIO_MIXER_WRITE = AUDIO_MIXER_WRITE;
unsigned IOCTL_AUDIO_MIXER_DEVINFO = AUDIO_MIXER_DEVINFO;
unsigned IOCTL_ATAIOCCOMMAND = ATAIOCCOMMAND;
unsigned IOCTL_ATABUSIOSCAN = ATABUSIOSCAN;
unsigned IOCTL_ATABUSIORESET = ATABUSIORESET;
unsigned IOCTL_ATABUSIODETACH = ATABUSIODETACH;
unsigned IOCTL_CDIOCPLAYTRACKS = CDIOCPLAYTRACKS;
unsigned IOCTL_CDIOCPLAYBLOCKS = CDIOCPLAYBLOCKS;
unsigned IOCTL_CDIOCREADSUBCHANNEL = CDIOCREADSUBCHANNEL;
unsigned IOCTL_CDIOREADTOCHEADER = CDIOREADTOCHEADER;
unsigned IOCTL_CDIOREADTOCENTRIES = CDIOREADTOCENTRIES;
unsigned IOCTL_CDIOREADMSADDR = CDIOREADMSADDR;
unsigned IOCTL_CDIOCSETPATCH = CDIOCSETPATCH;
unsigned IOCTL_CDIOCGETVOL = CDIOCGETVOL;
unsigned IOCTL_CDIOCSETVOL = CDIOCSETVOL;
unsigned IOCTL_CDIOCSETMONO = CDIOCSETMONO;
unsigned IOCTL_CDIOCSETSTEREO = CDIOCSETSTEREO;
unsigned IOCTL_CDIOCSETMUTE = CDIOCSETMUTE;
unsigned IOCTL_CDIOCSETLEFT = CDIOCSETLEFT;
unsigned IOCTL_CDIOCSETRIGHT = CDIOCSETRIGHT;
unsigned IOCTL_CDIOCSETDEBUG = CDIOCSETDEBUG;
unsigned IOCTL_CDIOCCLRDEBUG = CDIOCCLRDEBUG;
unsigned IOCTL_CDIOCPAUSE = CDIOCPAUSE;
unsigned IOCTL_CDIOCRESUME = CDIOCRESUME;
unsigned IOCTL_CDIOCRESET = CDIOCRESET;
unsigned IOCTL_CDIOCSTART = CDIOCSTART;
unsigned IOCTL_CDIOCSTOP = CDIOCSTOP;
unsigned IOCTL_CDIOCEJECT = CDIOCEJECT;
unsigned IOCTL_CDIOCALLOW = CDIOCALLOW;
unsigned IOCTL_CDIOCPREVENT = CDIOCPREVENT;
unsigned IOCTL_CDIOCCLOSE = CDIOCCLOSE;
unsigned IOCTL_CDIOCPLAYMSF = CDIOCPLAYMSF;
unsigned IOCTL_CDIOCLOADUNLOAD = CDIOCLOADUNLOAD;
unsigned IOCTL_CHIOMOVE = CHIOMOVE;
unsigned IOCTL_CHIOEXCHANGE = CHIOEXCHANGE;
unsigned IOCTL_CHIOPOSITION = CHIOPOSITION;
unsigned IOCTL_CHIOGPICKER = CHIOGPICKER;
unsigned IOCTL_CHIOSPICKER = CHIOSPICKER;
unsigned IOCTL_CHIOGPARAMS = CHIOGPARAMS;
unsigned IOCTL_CHIOIELEM = CHIOIELEM;
unsigned IOCTL_OCHIOGSTATUS = OCHIOGSTATUS;
unsigned IOCTL_CHIOGSTATUS = CHIOGSTATUS;
unsigned IOCTL_CHIOSVOLTAG = CHIOSVOLTAG;
unsigned IOCTL_CLOCKCTL_SETTIMEOFDAY = CLOCKCTL_SETTIMEOFDAY;
unsigned IOCTL_CLOCKCTL_ADJTIME = CLOCKCTL_ADJTIME;
unsigned IOCTL_CLOCKCTL_CLOCK_SETTIME = CLOCKCTL_CLOCK_SETTIME;
unsigned IOCTL_CLOCKCTL_NTP_ADJTIME = CLOCKCTL_NTP_ADJTIME;
unsigned IOCTL_IOC_CPU_SETSTATE = IOC_CPU_SETSTATE;
unsigned IOCTL_IOC_CPU_GETSTATE = IOC_CPU_GETSTATE;
unsigned IOCTL_IOC_CPU_GETCOUNT = IOC_CPU_GETCOUNT;
unsigned IOCTL_IOC_CPU_MAPID = IOC_CPU_MAPID;
unsigned IOCTL_IOC_CPU_UCODE_GET_VERSION = IOC_CPU_UCODE_GET_VERSION;
unsigned IOCTL_IOC_CPU_UCODE_APPLY = IOC_CPU_UCODE_APPLY;
unsigned IOCTL_DIOCGDINFO = DIOCGDINFO;
unsigned IOCTL_DIOCSDINFO = DIOCSDINFO;
unsigned IOCTL_DIOCWDINFO = DIOCWDINFO;
unsigned IOCTL_DIOCRFORMAT = DIOCRFORMAT;
unsigned IOCTL_DIOCWFORMAT = DIOCWFORMAT;
unsigned IOCTL_DIOCSSTEP = DIOCSSTEP;
unsigned IOCTL_DIOCSRETRIES = DIOCSRETRIES;
unsigned IOCTL_DIOCKLABEL = DIOCKLABEL;
unsigned IOCTL_DIOCWLABEL = DIOCWLABEL;
unsigned IOCTL_DIOCSBAD = DIOCSBAD;
unsigned IOCTL_DIOCEJECT = DIOCEJECT;
unsigned IOCTL_ODIOCEJECT = ODIOCEJECT;
unsigned IOCTL_DIOCLOCK = DIOCLOCK;
unsigned IOCTL_DIOCGDEFLABEL = DIOCGDEFLABEL;
unsigned IOCTL_DIOCCLRLABEL = DIOCCLRLABEL;
unsigned IOCTL_DIOCGCACHE = DIOCGCACHE;
unsigned IOCTL_DIOCSCACHE = DIOCSCACHE;
unsigned IOCTL_DIOCCACHESYNC = DIOCCACHESYNC;
unsigned IOCTL_DIOCBSLIST = DIOCBSLIST;
unsigned IOCTL_DIOCBSFLUSH = DIOCBSFLUSH;
unsigned IOCTL_DIOCAWEDGE = DIOCAWEDGE;
unsigned IOCTL_DIOCGWEDGEINFO = DIOCGWEDGEINFO;
unsigned IOCTL_DIOCDWEDGE = DIOCDWEDGE;
unsigned IOCTL_DIOCLWEDGES = DIOCLWEDGES;
unsigned IOCTL_DIOCGSTRATEGY = DIOCGSTRATEGY;
unsigned IOCTL_DIOCSSTRATEGY = DIOCSSTRATEGY;
unsigned IOCTL_DIOCGDISKINFO = DIOCGDISKINFO;
unsigned IOCTL_DIOCTUR = DIOCTUR;
unsigned IOCTL_DIOCMWEDGES = DIOCMWEDGES;
unsigned IOCTL_DIOCGSECTORSIZE = DIOCGSECTORSIZE;
unsigned IOCTL_DIOCGMEDIASIZE = DIOCGMEDIASIZE;
unsigned IOCTL_DRVDETACHDEV = DRVDETACHDEV;
unsigned IOCTL_DRVRESCANBUS = DRVRESCANBUS;
unsigned IOCTL_DRVCTLCOMMAND = DRVCTLCOMMAND;
unsigned IOCTL_DRVRESUMEDEV = DRVRESUMEDEV;
unsigned IOCTL_DRVLISTDEV = DRVLISTDEV;
unsigned IOCTL_DRVGETEVENT = DRVGETEVENT;
unsigned IOCTL_DRVSUSPENDDEV = DRVSUSPENDDEV;
unsigned IOCTL_DVD_READ_STRUCT = DVD_READ_STRUCT;
unsigned IOCTL_DVD_WRITE_STRUCT = DVD_WRITE_STRUCT;
unsigned IOCTL_DVD_AUTH = DVD_AUTH;
unsigned IOCTL_ENVSYS_GETDICTIONARY = ENVSYS_GETDICTIONARY;
unsigned IOCTL_ENVSYS_SETDICTIONARY = ENVSYS_SETDICTIONARY;
unsigned IOCTL_ENVSYS_REMOVEPROPS = ENVSYS_REMOVEPROPS;
unsigned IOCTL_ENVSYS_GTREDATA = ENVSYS_GTREDATA;
unsigned IOCTL_ENVSYS_GTREINFO = ENVSYS_GTREINFO;
unsigned IOCTL_KFILTER_BYFILTER = KFILTER_BYFILTER;
unsigned IOCTL_KFILTER_BYNAME = KFILTER_BYNAME;
unsigned IOCTL_FDIOCGETOPTS = FDIOCGETOPTS;
unsigned IOCTL_FDIOCSETOPTS = FDIOCSETOPTS;
unsigned IOCTL_FDIOCSETFORMAT = FDIOCSETFORMAT;
unsigned IOCTL_FDIOCGETFORMAT = FDIOCGETFORMAT;
unsigned IOCTL_FDIOCFORMAT_TRACK = FDIOCFORMAT_TRACK;
unsigned IOCTL_FIOCLEX = FIOCLEX;
unsigned IOCTL_FIONCLEX = FIONCLEX;
unsigned IOCTL_FIONREAD = FIONREAD;
unsigned IOCTL_FIONBIO = FIONBIO;
unsigned IOCTL_FIOASYNC = FIOASYNC;
unsigned IOCTL_FIOSETOWN = FIOSETOWN;
unsigned IOCTL_FIOGETOWN = FIOGETOWN;
unsigned IOCTL_OFIOGETBMAP = OFIOGETBMAP;
unsigned IOCTL_FIOGETBMAP = FIOGETBMAP;
unsigned IOCTL_FIONWRITE = FIONWRITE;
unsigned IOCTL_FIONSPACE = FIONSPACE;
unsigned IOCTL_GPIOINFO = GPIOINFO;
unsigned IOCTL_GPIOSET = GPIOSET;
unsigned IOCTL_GPIOUNSET = GPIOUNSET;
unsigned IOCTL_GPIOREAD = GPIOREAD;
unsigned IOCTL_GPIOWRITE = GPIOWRITE;
unsigned IOCTL_GPIOTOGGLE = GPIOTOGGLE;
unsigned IOCTL_GPIOATTACH = GPIOATTACH;
unsigned IOCTL_PTIOCNETBSD = PTIOCNETBSD;
unsigned IOCTL_PTIOCSUNOS = PTIOCSUNOS;
unsigned IOCTL_PTIOCLINUX = PTIOCLINUX;
unsigned IOCTL_PTIOCFREEBSD = PTIOCFREEBSD;
unsigned IOCTL_PTIOCULTRIX = PTIOCULTRIX;
unsigned IOCTL_TIOCHPCL = TIOCHPCL;
unsigned IOCTL_TIOCGETP = TIOCGETP;
unsigned IOCTL_TIOCSETP = TIOCSETP;
unsigned IOCTL_TIOCSETN = TIOCSETN;
unsigned IOCTL_TIOCSETC = TIOCSETC;
unsigned IOCTL_TIOCGETC = TIOCGETC;
unsigned IOCTL_TIOCLBIS = TIOCLBIS;
unsigned IOCTL_TIOCLBIC = TIOCLBIC;
unsigned IOCTL_TIOCLSET = TIOCLSET;
unsigned IOCTL_TIOCLGET = TIOCLGET;
unsigned IOCTL_TIOCSLTC = TIOCSLTC;
unsigned IOCTL_TIOCGLTC = TIOCGLTC;
unsigned IOCTL_OTIOCCONS = OTIOCCONS;
unsigned IOCTL_JOY_SETTIMEOUT = JOY_SETTIMEOUT;
unsigned IOCTL_JOY_GETTIMEOUT = JOY_GETTIMEOUT;
unsigned IOCTL_JOY_SET_X_OFFSET = JOY_SET_X_OFFSET;
unsigned IOCTL_JOY_SET_Y_OFFSET = JOY_SET_Y_OFFSET;
unsigned IOCTL_JOY_GET_X_OFFSET = JOY_GET_X_OFFSET;
unsigned IOCTL_JOY_GET_Y_OFFSET = JOY_GET_Y_OFFSET;
unsigned IOCTL_OKIOCGSYMBOL = OKIOCGSYMBOL;
unsigned IOCTL_OKIOCGVALUE = OKIOCGVALUE;
unsigned IOCTL_KIOCGSIZE = KIOCGSIZE;
unsigned IOCTL_KIOCGVALUE = KIOCGVALUE;
unsigned IOCTL_KIOCGSYMBOL = KIOCGSYMBOL;
unsigned IOCTL_LUAINFO = LUAINFO;
unsigned IOCTL_LUACREATE = LUACREATE;
unsigned IOCTL_LUADESTROY = LUADESTROY;
unsigned IOCTL_LUAREQUIRE = LUAREQUIRE;
unsigned IOCTL_LUALOAD = LUALOAD;
unsigned IOCTL_MIDI_PRETIME = MIDI_PRETIME;
unsigned IOCTL_MIDI_MPUMODE = MIDI_MPUMODE;
unsigned IOCTL_MIDI_MPUCMD = MIDI_MPUCMD;
unsigned IOCTL_SEQUENCER_RESET = SEQUENCER_RESET;
unsigned IOCTL_SEQUENCER_SYNC = SEQUENCER_SYNC;
unsigned IOCTL_SEQUENCER_INFO = SEQUENCER_INFO;
unsigned IOCTL_SEQUENCER_CTRLRATE = SEQUENCER_CTRLRATE;
unsigned IOCTL_SEQUENCER_GETOUTCOUNT = SEQUENCER_GETOUTCOUNT;
unsigned IOCTL_SEQUENCER_GETINCOUNT = SEQUENCER_GETINCOUNT;
unsigned IOCTL_SEQUENCER_RESETSAMPLES = SEQUENCER_RESETSAMPLES;
unsigned IOCTL_SEQUENCER_NRSYNTHS = SEQUENCER_NRSYNTHS;
unsigned IOCTL_SEQUENCER_NRMIDIS = SEQUENCER_NRMIDIS;
unsigned IOCTL_SEQUENCER_THRESHOLD = SEQUENCER_THRESHOLD;
unsigned IOCTL_SEQUENCER_MEMAVL = SEQUENCER_MEMAVL;
unsigned IOCTL_SEQUENCER_PANIC = SEQUENCER_PANIC;
unsigned IOCTL_SEQUENCER_OUTOFBAND = SEQUENCER_OUTOFBAND;
unsigned IOCTL_SEQUENCER_GETTIME = SEQUENCER_GETTIME;
unsigned IOCTL_SEQUENCER_TMR_TIMEBASE = SEQUENCER_TMR_TIMEBASE;
unsigned IOCTL_SEQUENCER_TMR_START = SEQUENCER_TMR_START;
unsigned IOCTL_SEQUENCER_TMR_STOP = SEQUENCER_TMR_STOP;
unsigned IOCTL_SEQUENCER_TMR_CONTINUE = SEQUENCER_TMR_CONTINUE;
unsigned IOCTL_SEQUENCER_TMR_TEMPO = SEQUENCER_TMR_TEMPO;
unsigned IOCTL_SEQUENCER_TMR_SOURCE = SEQUENCER_TMR_SOURCE;
unsigned IOCTL_SEQUENCER_TMR_METRONOME = SEQUENCER_TMR_METRONOME;
unsigned IOCTL_SEQUENCER_TMR_SELECT = SEQUENCER_TMR_SELECT;
unsigned IOCTL_MTIOCTOP = MTIOCTOP;
unsigned IOCTL_MTIOCGET = MTIOCGET;
unsigned IOCTL_MTIOCIEOT = MTIOCIEOT;
unsigned IOCTL_MTIOCEEOT = MTIOCEEOT;
unsigned IOCTL_MTIOCRDSPOS = MTIOCRDSPOS;
unsigned IOCTL_MTIOCRDHPOS = MTIOCRDHPOS;
unsigned IOCTL_MTIOCSLOCATE = MTIOCSLOCATE;
unsigned IOCTL_MTIOCHLOCATE = MTIOCHLOCATE;
unsigned IOCTL_POWER_EVENT_RECVDICT = POWER_EVENT_RECVDICT;
unsigned IOCTL_POWER_IOC_GET_TYPE = POWER_IOC_GET_TYPE;
unsigned IOCTL_POWER_IOC_GET_TYPE_WITH_LOSSAGE =
    POWER_IOC_GET_TYPE_WITH_LOSSAGE;
unsigned IOCTL_RIOCGINFO = RIOCGINFO;
unsigned IOCTL_RIOCSINFO = RIOCSINFO;
unsigned IOCTL_RIOCSSRCH = RIOCSSRCH;
unsigned IOCTL_RNDGETENTCNT = RNDGETENTCNT;
unsigned IOCTL_RNDGETSRCNUM = RNDGETSRCNUM;
unsigned IOCTL_RNDGETSRCNAME = RNDGETSRCNAME;
unsigned IOCTL_RNDCTL = RNDCTL;
unsigned IOCTL_RNDADDDATA = RNDADDDATA;
unsigned IOCTL_RNDGETPOOLSTAT = RNDGETPOOLSTAT;
unsigned IOCTL_RNDGETESTNUM = RNDGETESTNUM;
unsigned IOCTL_RNDGETESTNAME = RNDGETESTNAME;
unsigned IOCTL_SCIOCGET = SCIOCGET;
unsigned IOCTL_SCIOCSET = SCIOCSET;
unsigned IOCTL_SCIOCRESTART = SCIOCRESTART;
unsigned IOCTL_SCIOC_USE_ADF = SCIOC_USE_ADF;
unsigned IOCTL_SCIOCCOMMAND = SCIOCCOMMAND;
unsigned IOCTL_SCIOCDEBUG = SCIOCDEBUG;
unsigned IOCTL_SCIOCIDENTIFY = SCIOCIDENTIFY;
unsigned IOCTL_OSCIOCIDENTIFY = OSCIOCIDENTIFY;
unsigned IOCTL_SCIOCDECONFIG = SCIOCDECONFIG;
unsigned IOCTL_SCIOCRECONFIG = SCIOCRECONFIG;
unsigned IOCTL_SCIOCRESET = SCIOCRESET;
unsigned IOCTL_SCBUSIOSCAN = SCBUSIOSCAN;
unsigned IOCTL_SCBUSIORESET = SCBUSIORESET;
unsigned IOCTL_SCBUSIODETACH = SCBUSIODETACH;
unsigned IOCTL_SCBUSACCEL = SCBUSACCEL;
unsigned IOCTL_SCBUSIOLLSCAN = SCBUSIOLLSCAN;
unsigned IOCTL_SIOCSHIWAT = SIOCSHIWAT;
unsigned IOCTL_SIOCGHIWAT = SIOCGHIWAT;
unsigned IOCTL_SIOCSLOWAT = SIOCSLOWAT;
unsigned IOCTL_SIOCGLOWAT = SIOCGLOWAT;
unsigned IOCTL_SIOCATMARK = SIOCATMARK;
unsigned IOCTL_SIOCSPGRP = SIOCSPGRP;
unsigned IOCTL_SIOCGPGRP = SIOCGPGRP;
unsigned IOCTL_SIOCADDRT = SIOCADDRT;
unsigned IOCTL_SIOCDELRT = SIOCDELRT;
unsigned IOCTL_SIOCSIFADDR = SIOCSIFADDR;
unsigned IOCTL_SIOCGIFADDR = SIOCGIFADDR;
unsigned IOCTL_SIOCSIFDSTADDR = SIOCSIFDSTADDR;
unsigned IOCTL_SIOCGIFDSTADDR = SIOCGIFDSTADDR;
unsigned IOCTL_SIOCSIFFLAGS = SIOCSIFFLAGS;
unsigned IOCTL_SIOCGIFFLAGS = SIOCGIFFLAGS;
unsigned IOCTL_SIOCGIFBRDADDR = SIOCGIFBRDADDR;
unsigned IOCTL_SIOCSIFBRDADDR = SIOCSIFBRDADDR;
unsigned IOCTL_SIOCGIFCONF = SIOCGIFCONF;
unsigned IOCTL_SIOCGIFNETMASK = SIOCGIFNETMASK;
unsigned IOCTL_SIOCSIFNETMASK = SIOCSIFNETMASK;
unsigned IOCTL_SIOCGIFMETRIC = SIOCGIFMETRIC;
unsigned IOCTL_SIOCSIFMETRIC = SIOCSIFMETRIC;
unsigned IOCTL_SIOCDIFADDR = SIOCDIFADDR;
unsigned IOCTL_SIOCAIFADDR = SIOCAIFADDR;
unsigned IOCTL_SIOCGIFALIAS = SIOCGIFALIAS;
unsigned IOCTL_SIOCGIFAFLAG_IN = SIOCGIFAFLAG_IN;
unsigned IOCTL_SIOCALIFADDR = SIOCALIFADDR;
unsigned IOCTL_SIOCGLIFADDR = SIOCGLIFADDR;
unsigned IOCTL_SIOCDLIFADDR = SIOCDLIFADDR;
unsigned IOCTL_SIOCSIFADDRPREF = SIOCSIFADDRPREF;
unsigned IOCTL_SIOCGIFADDRPREF = SIOCGIFADDRPREF;
unsigned IOCTL_SIOCADDMULTI = SIOCADDMULTI;
unsigned IOCTL_SIOCDELMULTI = SIOCDELMULTI;
unsigned IOCTL_SIOCGETVIFCNT = SIOCGETVIFCNT;
unsigned IOCTL_SIOCGETSGCNT = SIOCGETSGCNT;
unsigned IOCTL_SIOCSIFMEDIA = SIOCSIFMEDIA;
unsigned IOCTL_SIOCGIFMEDIA = SIOCGIFMEDIA;
unsigned IOCTL_SIOCSIFGENERIC = SIOCSIFGENERIC;
unsigned IOCTL_SIOCGIFGENERIC = SIOCGIFGENERIC;
unsigned IOCTL_SIOCSIFPHYADDR = SIOCSIFPHYADDR;
unsigned IOCTL_SIOCGIFPSRCADDR = SIOCGIFPSRCADDR;
unsigned IOCTL_SIOCGIFPDSTADDR = SIOCGIFPDSTADDR;
unsigned IOCTL_SIOCDIFPHYADDR = SIOCDIFPHYADDR;
unsigned IOCTL_SIOCSLIFPHYADDR = SIOCSLIFPHYADDR;
unsigned IOCTL_SIOCGLIFPHYADDR = SIOCGLIFPHYADDR;
unsigned IOCTL_SIOCSIFMTU = SIOCSIFMTU;
unsigned IOCTL_SIOCGIFMTU = SIOCGIFMTU;
unsigned IOCTL_SIOCSDRVSPEC = SIOCSDRVSPEC;
unsigned IOCTL_SIOCGDRVSPEC = SIOCGDRVSPEC;
unsigned IOCTL_SIOCIFCREATE = SIOCIFCREATE;
unsigned IOCTL_SIOCIFDESTROY = SIOCIFDESTROY;
unsigned IOCTL_SIOCIFGCLONERS = SIOCIFGCLONERS;
unsigned IOCTL_SIOCGIFDLT = SIOCGIFDLT;
unsigned IOCTL_SIOCGIFCAP = SIOCGIFCAP;
unsigned IOCTL_SIOCSIFCAP = SIOCSIFCAP;
unsigned IOCTL_SIOCSVH = SIOCSVH;
unsigned IOCTL_SIOCGVH = SIOCGVH;
unsigned IOCTL_SIOCINITIFADDR = SIOCINITIFADDR;
unsigned IOCTL_SIOCGIFDATA = SIOCGIFDATA;
unsigned IOCTL_SIOCZIFDATA = SIOCZIFDATA;
unsigned IOCTL_SIOCGLINKSTR = SIOCGLINKSTR;
unsigned IOCTL_SIOCSLINKSTR = SIOCSLINKSTR;
unsigned IOCTL_SIOCGETHERCAP = SIOCGETHERCAP;
unsigned IOCTL_SIOCGIFINDEX = SIOCGIFINDEX;
unsigned IOCTL_SIOCSETPFSYNC = SIOCSETPFSYNC;
unsigned IOCTL_SIOCGETPFSYNC = SIOCGETPFSYNC;
unsigned IOCTL_PPS_IOC_CREATE = PPS_IOC_CREATE;
unsigned IOCTL_PPS_IOC_DESTROY = PPS_IOC_DESTROY;
unsigned IOCTL_PPS_IOC_SETPARAMS = PPS_IOC_SETPARAMS;
unsigned IOCTL_PPS_IOC_GETPARAMS = PPS_IOC_GETPARAMS;
unsigned IOCTL_PPS_IOC_GETCAP = PPS_IOC_GETCAP;
unsigned IOCTL_PPS_IOC_FETCH = PPS_IOC_FETCH;
unsigned IOCTL_PPS_IOC_KCBIND = PPS_IOC_KCBIND;
unsigned IOCTL_TIOCEXCL = TIOCEXCL;
unsigned IOCTL_TIOCNXCL = TIOCNXCL;
unsigned IOCTL_TIOCFLUSH = TIOCFLUSH;
unsigned IOCTL_TIOCGETA = TIOCGETA;
unsigned IOCTL_TIOCSETA = TIOCSETA;
unsigned IOCTL_TIOCSETAW = TIOCSETAW;
unsigned IOCTL_TIOCSETAF = TIOCSETAF;
unsigned IOCTL_TIOCGETD = TIOCGETD;
unsigned IOCTL_TIOCSETD = TIOCSETD;
unsigned IOCTL_TIOCGLINED = TIOCGLINED;
unsigned IOCTL_TIOCSLINED = TIOCSLINED;
unsigned IOCTL_TIOCSBRK = TIOCSBRK;
unsigned IOCTL_TIOCCBRK = TIOCCBRK;
unsigned IOCTL_TIOCSDTR = TIOCSDTR;
unsigned IOCTL_TIOCCDTR = TIOCCDTR;
unsigned IOCTL_TIOCGPGRP = TIOCGPGRP;
unsigned IOCTL_TIOCSPGRP = TIOCSPGRP;
unsigned IOCTL_TIOCOUTQ = TIOCOUTQ;
unsigned IOCTL_TIOCSTI = TIOCSTI;
unsigned IOCTL_TIOCNOTTY = TIOCNOTTY;
unsigned IOCTL_TIOCPKT = TIOCPKT;
unsigned IOCTL_TIOCSTOP = TIOCSTOP;
unsigned IOCTL_TIOCSTART = TIOCSTART;
unsigned IOCTL_TIOCMSET = TIOCMSET;
unsigned IOCTL_TIOCMBIS = TIOCMBIS;
unsigned IOCTL_TIOCMBIC = TIOCMBIC;
unsigned IOCTL_TIOCMGET = TIOCMGET;
unsigned IOCTL_TIOCREMOTE = TIOCREMOTE;
unsigned IOCTL_TIOCGWINSZ = TIOCGWINSZ;
unsigned IOCTL_TIOCSWINSZ = TIOCSWINSZ;
unsigned IOCTL_TIOCUCNTL = TIOCUCNTL;
unsigned IOCTL_TIOCSTAT = TIOCSTAT;
unsigned IOCTL_TIOCGSID = TIOCGSID;
unsigned IOCTL_TIOCCONS = TIOCCONS;
unsigned IOCTL_TIOCSCTTY = TIOCSCTTY;
unsigned IOCTL_TIOCEXT = TIOCEXT;
unsigned IOCTL_TIOCSIG = TIOCSIG;
unsigned IOCTL_TIOCDRAIN = TIOCDRAIN;
unsigned IOCTL_TIOCGFLAGS = TIOCGFLAGS;
unsigned IOCTL_TIOCSFLAGS = TIOCSFLAGS;
unsigned IOCTL_TIOCDCDTIMESTAMP = TIOCDCDTIMESTAMP;
unsigned IOCTL_TIOCRCVFRAME = TIOCRCVFRAME;
unsigned IOCTL_TIOCXMTFRAME = TIOCXMTFRAME;
unsigned IOCTL_TIOCPTMGET = TIOCPTMGET;
unsigned IOCTL_TIOCGRANTPT = TIOCGRANTPT;
unsigned IOCTL_TIOCPTSNAME = TIOCPTSNAME;
unsigned IOCTL_TIOCSQSIZE = TIOCSQSIZE;
unsigned IOCTL_TIOCGQSIZE = TIOCGQSIZE;
unsigned IOCTL_VERIEXEC_LOAD = VERIEXEC_LOAD;
unsigned IOCTL_VERIEXEC_TABLESIZE = VERIEXEC_TABLESIZE;
unsigned IOCTL_VERIEXEC_DELETE = VERIEXEC_DELETE;
unsigned IOCTL_VERIEXEC_QUERY = VERIEXEC_QUERY;
unsigned IOCTL_VERIEXEC_DUMP = VERIEXEC_DUMP;
unsigned IOCTL_VERIEXEC_FLUSH = VERIEXEC_FLUSH;
unsigned IOCTL_VIDIOC_QUERYCAP = VIDIOC_QUERYCAP;
unsigned IOCTL_VIDIOC_RESERVED = VIDIOC_RESERVED;
unsigned IOCTL_VIDIOC_ENUM_FMT = VIDIOC_ENUM_FMT;
unsigned IOCTL_VIDIOC_G_FMT = VIDIOC_G_FMT;
unsigned IOCTL_VIDIOC_S_FMT = VIDIOC_S_FMT;
unsigned IOCTL_VIDIOC_REQBUFS = VIDIOC_REQBUFS;
unsigned IOCTL_VIDIOC_QUERYBUF = VIDIOC_QUERYBUF;
unsigned IOCTL_VIDIOC_G_FBUF = VIDIOC_G_FBUF;
unsigned IOCTL_VIDIOC_S_FBUF = VIDIOC_S_FBUF;
unsigned IOCTL_VIDIOC_OVERLAY = VIDIOC_OVERLAY;
unsigned IOCTL_VIDIOC_QBUF = VIDIOC_QBUF;
unsigned IOCTL_VIDIOC_DQBUF = VIDIOC_DQBUF;
unsigned IOCTL_VIDIOC_STREAMON = VIDIOC_STREAMON;
unsigned IOCTL_VIDIOC_STREAMOFF = VIDIOC_STREAMOFF;
unsigned IOCTL_VIDIOC_G_PARM = VIDIOC_G_PARM;
unsigned IOCTL_VIDIOC_S_PARM = VIDIOC_S_PARM;
unsigned IOCTL_VIDIOC_G_STD = VIDIOC_G_STD;
unsigned IOCTL_VIDIOC_S_STD = VIDIOC_S_STD;
unsigned IOCTL_VIDIOC_ENUMSTD = VIDIOC_ENUMSTD;
unsigned IOCTL_VIDIOC_ENUMINPUT = VIDIOC_ENUMINPUT;
unsigned IOCTL_VIDIOC_G_CTRL = VIDIOC_G_CTRL;
unsigned IOCTL_VIDIOC_S_CTRL = VIDIOC_S_CTRL;
unsigned IOCTL_VIDIOC_G_TUNER = VIDIOC_G_TUNER;
unsigned IOCTL_VIDIOC_S_TUNER = VIDIOC_S_TUNER;
unsigned IOCTL_VIDIOC_G_AUDIO = VIDIOC_G_AUDIO;
unsigned IOCTL_VIDIOC_S_AUDIO = VIDIOC_S_AUDIO;
unsigned IOCTL_VIDIOC_QUERYCTRL = VIDIOC_QUERYCTRL;
unsigned IOCTL_VIDIOC_QUERYMENU = VIDIOC_QUERYMENU;
unsigned IOCTL_VIDIOC_G_INPUT = VIDIOC_G_INPUT;
unsigned IOCTL_VIDIOC_S_INPUT = VIDIOC_S_INPUT;
unsigned IOCTL_VIDIOC_G_OUTPUT = VIDIOC_G_OUTPUT;
unsigned IOCTL_VIDIOC_S_OUTPUT = VIDIOC_S_OUTPUT;
unsigned IOCTL_VIDIOC_ENUMOUTPUT = VIDIOC_ENUMOUTPUT;
unsigned IOCTL_VIDIOC_G_AUDOUT = VIDIOC_G_AUDOUT;
unsigned IOCTL_VIDIOC_S_AUDOUT = VIDIOC_S_AUDOUT;
unsigned IOCTL_VIDIOC_G_MODULATOR = VIDIOC_G_MODULATOR;
unsigned IOCTL_VIDIOC_S_MODULATOR = VIDIOC_S_MODULATOR;
unsigned IOCTL_VIDIOC_G_FREQUENCY = VIDIOC_G_FREQUENCY;
unsigned IOCTL_VIDIOC_S_FREQUENCY = VIDIOC_S_FREQUENCY;
unsigned IOCTL_VIDIOC_CROPCAP = VIDIOC_CROPCAP;
unsigned IOCTL_VIDIOC_G_CROP = VIDIOC_G_CROP;
unsigned IOCTL_VIDIOC_S_CROP = VIDIOC_S_CROP;
unsigned IOCTL_VIDIOC_G_JPEGCOMP = VIDIOC_G_JPEGCOMP;
unsigned IOCTL_VIDIOC_S_JPEGCOMP = VIDIOC_S_JPEGCOMP;
unsigned IOCTL_VIDIOC_QUERYSTD = VIDIOC_QUERYSTD;
unsigned IOCTL_VIDIOC_TRY_FMT = VIDIOC_TRY_FMT;
unsigned IOCTL_VIDIOC_ENUMAUDIO = VIDIOC_ENUMAUDIO;
unsigned IOCTL_VIDIOC_ENUMAUDOUT = VIDIOC_ENUMAUDOUT;
unsigned IOCTL_VIDIOC_G_PRIORITY = VIDIOC_G_PRIORITY;
unsigned IOCTL_VIDIOC_S_PRIORITY = VIDIOC_S_PRIORITY;
unsigned IOCTL_VIDIOC_ENUM_FRAMESIZES = VIDIOC_ENUM_FRAMESIZES;
unsigned IOCTL_VIDIOC_ENUM_FRAMEINTERVALS = VIDIOC_ENUM_FRAMEINTERVALS;
unsigned IOCTL_WDOGIOC_GMODE = WDOGIOC_GMODE;
unsigned IOCTL_WDOGIOC_SMODE = WDOGIOC_SMODE;
unsigned IOCTL_WDOGIOC_WHICH = WDOGIOC_WHICH;
unsigned IOCTL_WDOGIOC_TICKLE = WDOGIOC_TICKLE;
unsigned IOCTL_WDOGIOC_GTICKLER = WDOGIOC_GTICKLER;
unsigned IOCTL_WDOGIOC_GWDOGS = WDOGIOC_GWDOGS;
unsigned IOCTL_SNDCTL_DSP_RESET = SNDCTL_DSP_RESET;
unsigned IOCTL_SNDCTL_DSP_SYNC = SNDCTL_DSP_SYNC;
unsigned IOCTL_SNDCTL_DSP_SPEED = SNDCTL_DSP_SPEED;
unsigned IOCTL_SOUND_PCM_READ_RATE = SOUND_PCM_READ_RATE;
unsigned IOCTL_SNDCTL_DSP_STEREO = SNDCTL_DSP_STEREO;
unsigned IOCTL_SNDCTL_DSP_GETBLKSIZE = SNDCTL_DSP_GETBLKSIZE;
unsigned IOCTL_SNDCTL_DSP_SETFMT = SNDCTL_DSP_SETFMT;
unsigned IOCTL_SOUND_PCM_READ_BITS = SOUND_PCM_READ_BITS;
unsigned IOCTL_SNDCTL_DSP_CHANNELS = SNDCTL_DSP_CHANNELS;
unsigned IOCTL_SOUND_PCM_READ_CHANNELS = SOUND_PCM_READ_CHANNELS;
unsigned IOCTL_SOUND_PCM_WRITE_FILTER = SOUND_PCM_WRITE_FILTER;
unsigned IOCTL_SOUND_PCM_READ_FILTER = SOUND_PCM_READ_FILTER;
unsigned IOCTL_SNDCTL_DSP_POST = SNDCTL_DSP_POST;
unsigned IOCTL_SNDCTL_DSP_SUBDIVIDE = SNDCTL_DSP_SUBDIVIDE;
unsigned IOCTL_SNDCTL_DSP_SETFRAGMENT = SNDCTL_DSP_SETFRAGMENT;
unsigned IOCTL_SNDCTL_DSP_GETFMTS = SNDCTL_DSP_GETFMTS;
unsigned IOCTL_SNDCTL_DSP_GETOSPACE = SNDCTL_DSP_GETOSPACE;
unsigned IOCTL_SNDCTL_DSP_GETISPACE = SNDCTL_DSP_GETISPACE;
unsigned IOCTL_SNDCTL_DSP_NONBLOCK = SNDCTL_DSP_NONBLOCK;
unsigned IOCTL_SNDCTL_DSP_GETCAPS = SNDCTL_DSP_GETCAPS;
unsigned IOCTL_SNDCTL_DSP_GETTRIGGER = SNDCTL_DSP_GETTRIGGER;
unsigned IOCTL_SNDCTL_DSP_SETTRIGGER = SNDCTL_DSP_SETTRIGGER;
unsigned IOCTL_SNDCTL_DSP_GETIPTR = SNDCTL_DSP_GETIPTR;
unsigned IOCTL_SNDCTL_DSP_GETOPTR = SNDCTL_DSP_GETOPTR;
unsigned IOCTL_SNDCTL_DSP_MAPINBUF = SNDCTL_DSP_MAPINBUF;
unsigned IOCTL_SNDCTL_DSP_MAPOUTBUF = SNDCTL_DSP_MAPOUTBUF;
unsigned IOCTL_SNDCTL_DSP_SETSYNCRO = SNDCTL_DSP_SETSYNCRO;
unsigned IOCTL_SNDCTL_DSP_SETDUPLEX = SNDCTL_DSP_SETDUPLEX;
unsigned IOCTL_SNDCTL_DSP_PROFILE = SNDCTL_DSP_PROFILE;
unsigned IOCTL_SNDCTL_DSP_GETODELAY = SNDCTL_DSP_GETODELAY;
unsigned IOCTL_SOUND_MIXER_INFO = SOUND_MIXER_INFO;
unsigned IOCTL_SOUND_OLD_MIXER_INFO = SOUND_OLD_MIXER_INFO;
unsigned IOCTL_OSS_GETVERSION = OSS_GETVERSION;
unsigned IOCTL_SNDCTL_SYSINFO = SNDCTL_SYSINFO;
unsigned IOCTL_SNDCTL_AUDIOINFO = SNDCTL_AUDIOINFO;
unsigned IOCTL_SNDCTL_ENGINEINFO = SNDCTL_ENGINEINFO;
unsigned IOCTL_SNDCTL_DSP_GETPLAYVOL = SNDCTL_DSP_GETPLAYVOL;
unsigned IOCTL_SNDCTL_DSP_SETPLAYVOL = SNDCTL_DSP_SETPLAYVOL;
unsigned IOCTL_SNDCTL_DSP_GETRECVOL = SNDCTL_DSP_GETRECVOL;
unsigned IOCTL_SNDCTL_DSP_SETRECVOL = SNDCTL_DSP_SETRECVOL;
unsigned IOCTL_SNDCTL_DSP_SKIP = SNDCTL_DSP_SKIP;
unsigned IOCTL_SNDCTL_DSP_SILENCE = SNDCTL_DSP_SILENCE;

const int si_SEGV_MAPERR = SEGV_MAPERR;
const int si_SEGV_ACCERR = SEGV_ACCERR;
}  // namespace __sanitizer

using namespace __sanitizer;

COMPILER_CHECK(sizeof(__sanitizer_pthread_attr_t) >= sizeof(pthread_attr_t));

COMPILER_CHECK(sizeof(socklen_t) == sizeof(unsigned));
CHECK_TYPE_SIZE(pthread_key_t);

// There are more undocumented fields in dl_phdr_info that we are not interested
// in.
COMPILER_CHECK(sizeof(__sanitizer_dl_phdr_info) <= sizeof(dl_phdr_info));
CHECK_SIZE_AND_OFFSET(dl_phdr_info, dlpi_addr);
CHECK_SIZE_AND_OFFSET(dl_phdr_info, dlpi_name);
CHECK_SIZE_AND_OFFSET(dl_phdr_info, dlpi_phdr);
CHECK_SIZE_AND_OFFSET(dl_phdr_info, dlpi_phnum);

CHECK_TYPE_SIZE(glob_t);
CHECK_SIZE_AND_OFFSET(glob_t, gl_pathc);
CHECK_SIZE_AND_OFFSET(glob_t, gl_pathv);
CHECK_SIZE_AND_OFFSET(glob_t, gl_offs);
CHECK_SIZE_AND_OFFSET(glob_t, gl_flags);
CHECK_SIZE_AND_OFFSET(glob_t, gl_closedir);
CHECK_SIZE_AND_OFFSET(glob_t, gl_readdir);
CHECK_SIZE_AND_OFFSET(glob_t, gl_opendir);
CHECK_SIZE_AND_OFFSET(glob_t, gl_lstat);
CHECK_SIZE_AND_OFFSET(glob_t, gl_stat);

CHECK_TYPE_SIZE(addrinfo);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_flags);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_family);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_socktype);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_protocol);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_protocol);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_addrlen);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_canonname);
CHECK_SIZE_AND_OFFSET(addrinfo, ai_addr);

CHECK_TYPE_SIZE(hostent);
CHECK_SIZE_AND_OFFSET(hostent, h_name);
CHECK_SIZE_AND_OFFSET(hostent, h_aliases);
CHECK_SIZE_AND_OFFSET(hostent, h_addrtype);
CHECK_SIZE_AND_OFFSET(hostent, h_length);
CHECK_SIZE_AND_OFFSET(hostent, h_addr_list);

CHECK_TYPE_SIZE(iovec);
CHECK_SIZE_AND_OFFSET(iovec, iov_base);
CHECK_SIZE_AND_OFFSET(iovec, iov_len);

CHECK_TYPE_SIZE(msghdr);
CHECK_SIZE_AND_OFFSET(msghdr, msg_name);
CHECK_SIZE_AND_OFFSET(msghdr, msg_namelen);
CHECK_SIZE_AND_OFFSET(msghdr, msg_iov);
CHECK_SIZE_AND_OFFSET(msghdr, msg_iovlen);
CHECK_SIZE_AND_OFFSET(msghdr, msg_control);
CHECK_SIZE_AND_OFFSET(msghdr, msg_controllen);
CHECK_SIZE_AND_OFFSET(msghdr, msg_flags);

CHECK_TYPE_SIZE(cmsghdr);
CHECK_SIZE_AND_OFFSET(cmsghdr, cmsg_len);
CHECK_SIZE_AND_OFFSET(cmsghdr, cmsg_level);
CHECK_SIZE_AND_OFFSET(cmsghdr, cmsg_type);

COMPILER_CHECK(sizeof(__sanitizer_dirent) <= sizeof(dirent));
CHECK_SIZE_AND_OFFSET(dirent, d_fileno);
CHECK_SIZE_AND_OFFSET(dirent, d_reclen);

CHECK_TYPE_SIZE(ifconf);
CHECK_SIZE_AND_OFFSET(ifconf, ifc_len);
CHECK_SIZE_AND_OFFSET(ifconf, ifc_ifcu);

CHECK_TYPE_SIZE(pollfd);
CHECK_SIZE_AND_OFFSET(pollfd, fd);
CHECK_SIZE_AND_OFFSET(pollfd, events);
CHECK_SIZE_AND_OFFSET(pollfd, revents);

CHECK_TYPE_SIZE(nfds_t);

CHECK_TYPE_SIZE(sigset_t);

COMPILER_CHECK(sizeof(__sanitizer_sigaction) == sizeof(struct sigaction));
// Can't write checks for sa_handler and sa_sigaction due to them being
// preprocessor macros.
CHECK_STRUCT_SIZE_AND_OFFSET(sigaction, sa_mask);

CHECK_TYPE_SIZE(wordexp_t);
CHECK_SIZE_AND_OFFSET(wordexp_t, we_wordc);
CHECK_SIZE_AND_OFFSET(wordexp_t, we_wordv);
CHECK_SIZE_AND_OFFSET(wordexp_t, we_offs);

CHECK_TYPE_SIZE(tm);
CHECK_SIZE_AND_OFFSET(tm, tm_sec);
CHECK_SIZE_AND_OFFSET(tm, tm_min);
CHECK_SIZE_AND_OFFSET(tm, tm_hour);
CHECK_SIZE_AND_OFFSET(tm, tm_mday);
CHECK_SIZE_AND_OFFSET(tm, tm_mon);
CHECK_SIZE_AND_OFFSET(tm, tm_year);
CHECK_SIZE_AND_OFFSET(tm, tm_wday);
CHECK_SIZE_AND_OFFSET(tm, tm_yday);
CHECK_SIZE_AND_OFFSET(tm, tm_isdst);
CHECK_SIZE_AND_OFFSET(tm, tm_gmtoff);
CHECK_SIZE_AND_OFFSET(tm, tm_zone);

CHECK_TYPE_SIZE(ether_addr);

CHECK_TYPE_SIZE(ipc_perm);
CHECK_SIZE_AND_OFFSET(ipc_perm, _key);
CHECK_SIZE_AND_OFFSET(ipc_perm, _seq);
CHECK_SIZE_AND_OFFSET(ipc_perm, uid);
CHECK_SIZE_AND_OFFSET(ipc_perm, gid);
CHECK_SIZE_AND_OFFSET(ipc_perm, cuid);
CHECK_SIZE_AND_OFFSET(ipc_perm, cgid);
CHECK_SIZE_AND_OFFSET(ipc_perm, mode);

CHECK_TYPE_SIZE(shmid_ds);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_perm);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_segsz);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_atime);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_dtime);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_ctime);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_cpid);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_lpid);
CHECK_SIZE_AND_OFFSET(shmid_ds, shm_nattch);

CHECK_TYPE_SIZE(clock_t);

CHECK_TYPE_SIZE(ifaddrs);
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_next);
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_name);
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_addr);
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_netmask);
// Compare against the union, because we can't reach into the union in a
// compliant way.
#ifdef ifa_dstaddr
#undef ifa_dstaddr
#endif
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_dstaddr);
CHECK_SIZE_AND_OFFSET(ifaddrs, ifa_data);

CHECK_TYPE_SIZE(timeb);
CHECK_SIZE_AND_OFFSET(timeb, time);
CHECK_SIZE_AND_OFFSET(timeb, millitm);
CHECK_SIZE_AND_OFFSET(timeb, timezone);
CHECK_SIZE_AND_OFFSET(timeb, dstflag);

CHECK_TYPE_SIZE(passwd);
CHECK_SIZE_AND_OFFSET(passwd, pw_name);
CHECK_SIZE_AND_OFFSET(passwd, pw_passwd);
CHECK_SIZE_AND_OFFSET(passwd, pw_uid);
CHECK_SIZE_AND_OFFSET(passwd, pw_gid);
CHECK_SIZE_AND_OFFSET(passwd, pw_dir);
CHECK_SIZE_AND_OFFSET(passwd, pw_shell);

CHECK_SIZE_AND_OFFSET(passwd, pw_gecos);

CHECK_TYPE_SIZE(group);
CHECK_SIZE_AND_OFFSET(group, gr_name);
CHECK_SIZE_AND_OFFSET(group, gr_passwd);
CHECK_SIZE_AND_OFFSET(group, gr_gid);
CHECK_SIZE_AND_OFFSET(group, gr_mem);

#endif  // SANITIZER_NETBSD
