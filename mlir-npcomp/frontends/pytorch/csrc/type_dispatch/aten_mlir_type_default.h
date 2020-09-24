//===- aten_mlir_type_default.h ---------------------------------*- C++ -*-===//
//
// This file is licensed under a pytorch-style license
// See frontends/pytorch/LICENSE for license information.
//
//===----------------------------------------------------------------------===//

#include <ATen/Tensor.h>

namespace torch_mlir {

class ATenMLIRTypeDefault {
public:
  static at::Tensor _cast_Byte(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Char(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Double(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Float(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Int(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Long(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Short(const at::Tensor &self, bool non_blocking);
  static at::Tensor _cast_Half(const at::Tensor &self, bool non_blocking);
  static void backward(const at::Tensor &self, const at::Tensor &gradient,
                       bool keep_graph, bool create_graph);
  static void set_data(const at::Tensor &self, const at::Tensor &new_data);
  static at::Tensor data(const at::Tensor &self);
  static int64_t _debug_has_internal_overlap(const at::Tensor &self);
  static std::tuple<at::Tensor, at::Tensor>
  _fused_dropout(const at::Tensor &self, double p, at::Generator *generator);
  static at::Tensor _masked_scale(const at::Tensor &self,
                                  const at::Tensor &mask, double scale);
  static std::tuple<at::Tensor, at::Tensor>
  _sobol_engine_draw(const at::Tensor &quasi, int64_t n,
                     const at::Tensor &sobolstate, int64_t dimension,
                     int64_t num_generated,
                     c10::optional<at::ScalarType> dtype);
  static at::Tensor &_sobol_engine_ff_(at::Tensor &self, int64_t n,
                                       const at::Tensor &sobolstate,
                                       int64_t dimension,
                                       int64_t num_generated);
  static at::Tensor &_sobol_engine_scramble_(at::Tensor &self,
                                             const at::Tensor &ltm,
                                             int64_t dimension);
  static at::Tensor &_sobol_engine_initialize_state_(at::Tensor &self,
                                                     int64_t dimension);
  static at::Tensor _reshape_from_tensor(const at::Tensor &self,
                                         const at::Tensor &shape);
  static at::Tensor _shape_as_tensor(const at::Tensor &self);
  static at::Tensor dropout(const at::Tensor &input, double p, bool train);
  static at::Tensor &dropout_(at::Tensor &self, double p, bool train);
  static at::Tensor feature_dropout(const at::Tensor &input, double p,
                                    bool train);
  static at::Tensor &feature_dropout_(at::Tensor &self, double p, bool train);
  static at::Tensor alpha_dropout(const at::Tensor &input, double p,
                                  bool train);
  static at::Tensor &alpha_dropout_(at::Tensor &self, double p, bool train);
  static at::Tensor feature_alpha_dropout(const at::Tensor &input, double p,
                                          bool train);
  static at::Tensor &feature_alpha_dropout_(at::Tensor &self, double p,
                                            bool train);
  static at::Tensor abs(const at::Tensor &self);
  static at::Tensor &abs_(at::Tensor &self);
  static at::Tensor &abs_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor acos(const at::Tensor &self);
  static at::Tensor &acos_(at::Tensor &self);
  static at::Tensor &acos_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor avg_pool1d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               bool ceil_mode, bool count_include_pad);
  static at::Tensor adaptive_avg_pool1d(const at::Tensor &self,
                                        at::IntArrayRef output_size);
  static std::tuple<at::Tensor, at::Tensor>
  adaptive_max_pool1d(const at::Tensor &self, at::IntArrayRef output_size);
  static at::Tensor add(const at::Tensor &self, const at::Tensor &other,
                        at::Scalar alpha);
  static at::Tensor &add_(at::Tensor &self, const at::Tensor &other,
                          at::Scalar alpha);
  static at::Tensor &add_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other, at::Scalar alpha);
  static at::Tensor add(const at::Tensor &self, at::Scalar other,
                        at::Scalar alpha);
  static at::Tensor &add_(at::Tensor &self, at::Scalar other, at::Scalar alpha);
  static at::Tensor addmv(const at::Tensor &self, const at::Tensor &mat,
                          const at::Tensor &vec, at::Scalar beta,
                          at::Scalar alpha);
  static at::Tensor &addmv_(at::Tensor &self, const at::Tensor &mat,
                            const at::Tensor &vec, at::Scalar beta,
                            at::Scalar alpha);
  static at::Tensor &addmv_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &mat, const at::Tensor &vec,
                               at::Scalar beta, at::Scalar alpha);
  static at::Tensor addr(const at::Tensor &self, const at::Tensor &vec1,
                         const at::Tensor &vec2, at::Scalar beta,
                         at::Scalar alpha);
  static at::Tensor &addr_(at::Tensor &self, const at::Tensor &vec1,
                           const at::Tensor &vec2, at::Scalar beta,
                           at::Scalar alpha);
  static at::Tensor &addr_out(at::Tensor &out, const at::Tensor &self,
                              const at::Tensor &vec1, const at::Tensor &vec2,
                              at::Scalar beta, at::Scalar alpha);
  static at::Tensor affine_grid_generator(const at::Tensor &theta,
                                          at::IntArrayRef size,
                                          bool align_corners);
  static at::Tensor affine_grid_generator_backward(const at::Tensor &grad,
                                                   at::IntArrayRef size,
                                                   bool align_corners);
  static at::Tensor all(const at::Tensor &self, int64_t dim, bool keepdim);
  static at::Tensor &all_out(at::Tensor &out, const at::Tensor &self,
                             int64_t dim, bool keepdim);
  static bool allclose(const at::Tensor &self, const at::Tensor &other,
                       double rtol, double atol, bool equal_nan);
  static at::Tensor any(const at::Tensor &self, int64_t dim, bool keepdim);
  static at::Tensor &any_out(at::Tensor &out, const at::Tensor &self,
                             int64_t dim, bool keepdim);
  static at::Tensor arange(at::Scalar end, const at::TensorOptions &options);
  static at::Tensor arange(at::Scalar start, at::Scalar end,
                           const at::TensorOptions &options);
  static at::Tensor arange(at::Scalar start, at::Scalar end, at::Scalar step,
                           const at::TensorOptions &options);
  static at::Tensor &arange_out(at::Tensor &out, at::Scalar end);
  static at::Tensor &arange_out(at::Tensor &out, at::Scalar start,
                                at::Scalar end, at::Scalar step);
  static at::Tensor _dim_arange(const at::Tensor &like, int64_t dim);
  static at::Tensor argmax(const at::Tensor &self, c10::optional<int64_t> dim,
                           bool keepdim);
  static at::Tensor argmin(const at::Tensor &self, c10::optional<int64_t> dim,
                           bool keepdim);
  static at::Tensor as_strided(const at::Tensor &self, at::IntArrayRef size,
                               at::IntArrayRef stride,
                               c10::optional<int64_t> storage_offset);
  static at::Tensor &as_strided_(at::Tensor &self, at::IntArrayRef size,
                                 at::IntArrayRef stride,
                                 c10::optional<int64_t> storage_offset);
  static at::Tensor asin(const at::Tensor &self);
  static at::Tensor &asin_(at::Tensor &self);
  static at::Tensor &asin_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor atan(const at::Tensor &self);
  static at::Tensor &atan_(at::Tensor &self);
  static at::Tensor &atan_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor baddbmm(const at::Tensor &self, const at::Tensor &batch1,
                            const at::Tensor &batch2, at::Scalar beta,
                            at::Scalar alpha);
  static at::Tensor &baddbmm_(at::Tensor &self, const at::Tensor &batch1,
                              const at::Tensor &batch2, at::Scalar beta,
                              at::Scalar alpha);
  static at::Tensor &_baddbmm_mkl_(at::Tensor &self, const at::Tensor &batch1,
                                   const at::Tensor &batch2, at::Scalar beta,
                                   at::Scalar alpha);
  static at::Tensor &baddbmm_out(at::Tensor &out, const at::Tensor &self,
                                 const at::Tensor &batch1,
                                 const at::Tensor &batch2, at::Scalar beta,
                                 at::Scalar alpha);
  static at::Tensor bartlett_window(int64_t window_length,
                                    const at::TensorOptions &options);
  static at::Tensor bartlett_window(int64_t window_length, bool periodic,
                                    const at::TensorOptions &options);
  static at::Tensor batch_norm(const at::Tensor &input,
                               const at::Tensor &weight, const at::Tensor &bias,
                               const at::Tensor &running_mean,
                               const at::Tensor &running_var, bool training,
                               double momentum, double eps, bool cudnn_enabled);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, int64_t>
  _batch_norm_impl_index(const at::Tensor &input, const at::Tensor &weight,
                         const at::Tensor &bias, const at::Tensor &running_mean,
                         const at::Tensor &running_var, bool training,
                         double momentum, double eps, bool cudnn_enabled);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _batch_norm_impl_index_backward(
      int64_t impl_index, const at::Tensor &input,
      const at::Tensor &grad_output, const at::Tensor &weight,
      const at::Tensor &running_mean, const at::Tensor &running_var,
      const at::Tensor &save_mean, const at::Tensor &save_var_transform,
      bool train, double eps, std::array<bool, 3> output_mask);
  static at::Tensor bernoulli(const at::Tensor &self, at::Generator *generator);
  static at::Tensor &bernoulli_out(at::Tensor &out, const at::Tensor &self,
                                   at::Generator *generator);
  static at::Tensor &bernoulli_(at::Tensor &self, const at::Tensor &p,
                                at::Generator *generator);
  static at::Tensor &bernoulli_(at::Tensor &self, double p,
                                at::Generator *generator);
  static at::Tensor bernoulli(const at::Tensor &self, double p,
                              at::Generator *generator);
  static at::Tensor bilinear(const at::Tensor &input1, const at::Tensor &input2,
                             const at::Tensor &weight, const at::Tensor &bias);
  static at::Tensor binary_cross_entropy_with_logits(
      const at::Tensor &self, const at::Tensor &target,
      const at::Tensor &weight, const at::Tensor &pos_weight,
      int64_t reduction);
  static at::Tensor binary_cross_entropy_with_logits_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &target, const at::Tensor &weight,
      const at::Tensor &pos_weight, int64_t reduction);
  static at::Tensor bincount(const at::Tensor &self, const at::Tensor &weights,
                             int64_t minlength);
  static at::Tensor bitwise_not(const at::Tensor &self);
  static at::Tensor &bitwise_not_(at::Tensor &self);
  static at::Tensor &bitwise_not_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor logical_not(const at::Tensor &self);
  static at::Tensor &logical_not_(at::Tensor &self);
  static at::Tensor &logical_not_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor logical_xor(const at::Tensor &self,
                                const at::Tensor &other);
  static at::Tensor &logical_xor_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &logical_xor_out(at::Tensor &out, const at::Tensor &self,
                                     const at::Tensor &other);
  static at::Tensor blackman_window(int64_t window_length,
                                    const at::TensorOptions &options);
  static at::Tensor blackman_window(int64_t window_length, bool periodic,
                                    const at::TensorOptions &options);
  static at::Tensor bmm(const at::Tensor &self, const at::Tensor &mat2);
  static at::Tensor &bmm_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &mat2);
  static std::vector<at::Tensor> broadcast_tensors(at::TensorList tensors);
  static at::Tensor cat(at::TensorList tensors, int64_t dim);
  static at::Tensor &cat_out(at::Tensor &out, at::TensorList tensors,
                             int64_t dim);
  static at::Tensor ceil(const at::Tensor &self);
  static at::Tensor &ceil_(at::Tensor &self);
  static at::Tensor &ceil_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor chain_matmul(at::TensorList matrices);
  static std::vector<at::Tensor> chunk(const at::Tensor &self, int64_t chunks,
                                       int64_t dim);
  static at::Tensor clamp(const at::Tensor &self, c10::optional<at::Scalar> min,
                          c10::optional<at::Scalar> max);
  static at::Tensor &clamp_(at::Tensor &self, c10::optional<at::Scalar> min,
                            c10::optional<at::Scalar> max);
  static at::Tensor &clamp_out(at::Tensor &out, const at::Tensor &self,
                               c10::optional<at::Scalar> min,
                               c10::optional<at::Scalar> max);
  static at::Tensor clamp_max(const at::Tensor &self, at::Scalar max);
  static at::Tensor &clamp_max_(at::Tensor &self, at::Scalar max);
  static at::Tensor &clamp_max_out(at::Tensor &out, const at::Tensor &self,
                                   at::Scalar max);
  static at::Tensor clamp_min(const at::Tensor &self, at::Scalar min);
  static at::Tensor &clamp_min_(at::Tensor &self, at::Scalar min);
  static at::Tensor &clamp_min_out(at::Tensor &out, const at::Tensor &self,
                                   at::Scalar min);
  static at::Tensor constant_pad_nd(const at::Tensor &self, at::IntArrayRef pad,
                                    at::Scalar value);
  static at::Tensor contiguous(const at::Tensor &self,
                               at::MemoryFormat memory_format);
  static at::Tensor convolution(const at::Tensor &input,
                                const at::Tensor &weight,
                                const at::Tensor &bias, at::IntArrayRef stride,
                                at::IntArrayRef padding,
                                at::IntArrayRef dilation, bool transposed,
                                at::IntArrayRef output_padding, int64_t groups);
  static at::Tensor convolution_overrideable(
      const at::Tensor &input, const at::Tensor &weight, const at::Tensor &bias,
      at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation,
      bool transposed, at::IntArrayRef output_padding, int64_t groups);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  convolution_backward_overrideable(
      const at::Tensor &grad_output, const at::Tensor &input,
      const at::Tensor &weight, at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef dilation, bool transposed, at::IntArrayRef output_padding,
      int64_t groups, std::array<bool, 3> output_mask);
  static at::Tensor
  _convolution(const at::Tensor &input, const at::Tensor &weight,
               const at::Tensor &bias, at::IntArrayRef stride,
               at::IntArrayRef padding, at::IntArrayRef dilation,
               bool transposed, at::IntArrayRef output_padding, int64_t groups,
               bool benchmark, bool deterministic, bool cudnn_enabled);
  static at::Tensor
  _convolution_nogroup(const at::Tensor &input, const at::Tensor &weight,
                       const at::Tensor &bias, at::IntArrayRef stride,
                       at::IntArrayRef padding, at::IntArrayRef dilation,
                       bool transposed, at::IntArrayRef output_padding);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _convolution_double_backward(const at::Tensor &ggI, const at::Tensor &ggW,
                               const at::Tensor &ggb, const at::Tensor &gO,
                               const at::Tensor &weight, const at::Tensor &self,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation, bool transposed,
                               at::IntArrayRef output_padding, int64_t groups,
                               bool benchmark, bool deterministic,
                               bool cudnn_enabled,
                               std::array<bool, 3> output_mask);
  static at::Tensor conv1d(const at::Tensor &input, const at::Tensor &weight,
                           const at::Tensor &bias, at::IntArrayRef stride,
                           at::IntArrayRef padding, at::IntArrayRef dilation,
                           int64_t groups);
  static at::Tensor conv2d(const at::Tensor &input, const at::Tensor &weight,
                           const at::Tensor &bias, at::IntArrayRef stride,
                           at::IntArrayRef padding, at::IntArrayRef dilation,
                           int64_t groups);
  static at::Tensor conv3d(const at::Tensor &input, const at::Tensor &weight,
                           const at::Tensor &bias, at::IntArrayRef stride,
                           at::IntArrayRef padding, at::IntArrayRef dilation,
                           int64_t groups);
  static at::Tensor conv_tbc(const at::Tensor &self, const at::Tensor &weight,
                             const at::Tensor &bias, int64_t pad);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  conv_tbc_backward(const at::Tensor &self, const at::Tensor &input,
                    const at::Tensor &weight, const at::Tensor &bias,
                    int64_t pad);
  static at::Tensor
  conv_transpose1d(const at::Tensor &input, const at::Tensor &weight,
                   const at::Tensor &bias, at::IntArrayRef stride,
                   at::IntArrayRef padding, at::IntArrayRef output_padding,
                   int64_t groups, at::IntArrayRef dilation);
  static at::Tensor
  conv_transpose2d(const at::Tensor &input, const at::Tensor &weight,
                   const at::Tensor &bias, at::IntArrayRef stride,
                   at::IntArrayRef padding, at::IntArrayRef output_padding,
                   int64_t groups, at::IntArrayRef dilation);
  static at::Tensor
  conv_transpose3d(const at::Tensor &input, const at::Tensor &weight,
                   const at::Tensor &bias, at::IntArrayRef stride,
                   at::IntArrayRef padding, at::IntArrayRef output_padding,
                   int64_t groups, at::IntArrayRef dilation);
  static at::Tensor &copy_(at::Tensor &self, const at::Tensor &src,
                           bool non_blocking);
  static at::Tensor _copy_from(const at::Tensor &self, const at::Tensor &dst,
                               bool non_blocking);
  static at::Tensor cos(const at::Tensor &self);
  static at::Tensor &cos_(at::Tensor &self);
  static at::Tensor &cos_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor cosh(const at::Tensor &self);
  static at::Tensor &cosh_(at::Tensor &self);
  static at::Tensor &cosh_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor cosine_embedding_loss(const at::Tensor &input1,
                                          const at::Tensor &input2,
                                          const at::Tensor &target,
                                          double margin, int64_t reduction);
  static at::Tensor cumsum(const at::Tensor &self, int64_t dim,
                           c10::optional<at::ScalarType> dtype);
  static at::Tensor &cumsum_out(at::Tensor &out, const at::Tensor &self,
                                int64_t dim,
                                c10::optional<at::ScalarType> dtype);
  static at::Tensor cumprod(const at::Tensor &self, int64_t dim,
                            c10::optional<at::ScalarType> dtype);
  static at::Tensor &cumprod_out(at::Tensor &out, const at::Tensor &self,
                                 int64_t dim,
                                 c10::optional<at::ScalarType> dtype);
  static at::Tensor ctc_loss(const at::Tensor &log_probs,
                             const at::Tensor &targets,
                             at::IntArrayRef input_lengths,
                             at::IntArrayRef target_lengths, int64_t blank,
                             int64_t reduction, bool zero_infinity);
  static at::Tensor ctc_loss(const at::Tensor &log_probs,
                             const at::Tensor &targets,
                             const at::Tensor &input_lengths,
                             const at::Tensor &target_lengths, int64_t blank,
                             int64_t reduction, bool zero_infinity);
  static std::tuple<at::Tensor, at::Tensor>
  _ctc_loss(const at::Tensor &log_probs, const at::Tensor &targets,
            at::IntArrayRef input_lengths, at::IntArrayRef target_lengths,
            int64_t blank, bool zero_infinity);
  static at::Tensor _ctc_loss_backward(
      const at::Tensor &grad, const at::Tensor &log_probs,
      const at::Tensor &targets, at::IntArrayRef input_lengths,
      at::IntArrayRef target_lengths, const at::Tensor &neg_log_likelihood,
      const at::Tensor &log_alpha, int64_t blank, bool zero_infinity);
  static at::Tensor det(const at::Tensor &self);
  static at::Tensor diag_embed(const at::Tensor &self, int64_t offset,
                               int64_t dim1, int64_t dim2);
  static at::Tensor diagflat(const at::Tensor &self, int64_t offset);
  static at::Tensor diagonal(const at::Tensor &self, int64_t offset,
                             int64_t dim1, int64_t dim2);
  static at::Tensor &fill_diagonal_(at::Tensor &self, at::Scalar fill_value,
                                    bool wrap);
  static at::Tensor div(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &div_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &div_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other);
  static at::Tensor div(const at::Tensor &self, at::Scalar other);
  static at::Tensor &div_(at::Tensor &self, at::Scalar other);
  static at::Tensor dot(const at::Tensor &self, const at::Tensor &tensor);
  static at::Tensor &dot_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &tensor);
  static at::Tensor einsum(std::string equation, at::TensorList tensors);
  static at::Tensor embedding(const at::Tensor &weight,
                              const at::Tensor &indices, int64_t padding_idx,
                              bool scale_grad_by_freq, bool sparse);
  static at::Tensor embedding_backward(const at::Tensor &grad,
                                       const at::Tensor &indices,
                                       int64_t num_weights, int64_t padding_idx,
                                       bool scale_grad_by_freq, bool sparse);
  static at::Tensor embedding_dense_backward(const at::Tensor &grad_output,
                                             const at::Tensor &indices,
                                             int64_t num_weights,
                                             int64_t padding_idx,
                                             bool scale_grad_by_freq);
  static at::Tensor &embedding_renorm_(at::Tensor &self,
                                       const at::Tensor &indices,
                                       double max_norm, double norm_type);
  static at::Tensor embedding_sparse_backward(const at::Tensor &grad,
                                              const at::Tensor &indices,
                                              int64_t num_weights,
                                              int64_t padding_idx,
                                              bool scale_grad_by_freq);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  embedding_bag(const at::Tensor &weight, const at::Tensor &indices,
                const at::Tensor &offsets, bool scale_grad_by_freq,
                int64_t mode, bool sparse,
                const at::Tensor &per_sample_weights);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  _embedding_bag(const at::Tensor &weight, const at::Tensor &indices,
                 const at::Tensor &offsets, bool scale_grad_by_freq,
                 int64_t mode, bool sparse,
                 const at::Tensor &per_sample_weights);
  static at::Tensor _embedding_bag_backward(
      const at::Tensor &grad, const at::Tensor &indices,
      const at::Tensor &offsets, const at::Tensor &offset2bag,
      const at::Tensor &bag_size, const at::Tensor &maximum_indices,
      int64_t num_weights, bool scale_grad_by_freq, int64_t mode, bool sparse,
      const at::Tensor &per_sample_weights);
  static at::Tensor _embedding_bag_sparse_backward(
      const at::Tensor &grad, const at::Tensor &indices,
      const at::Tensor &offsets, const at::Tensor &offset2bag,
      const at::Tensor &bag_size, int64_t num_weights, bool scale_grad_by_freq,
      int64_t mode, const at::Tensor &per_sample_weights);
  static at::Tensor _embedding_bag_dense_backward(
      const at::Tensor &grad, const at::Tensor &indices,
      const at::Tensor &offsets, const at::Tensor &offset2bag,
      const at::Tensor &bag_size, const at::Tensor &maximum_indices,
      int64_t num_weights, bool scale_grad_by_freq, int64_t mode,
      const at::Tensor &per_sample_weights);
  static at::Tensor _embedding_bag_per_sample_weights_backward(
      const at::Tensor &grad, const at::Tensor &weight,
      const at::Tensor &indices, const at::Tensor &offsets,
      const at::Tensor &offset2bag, int64_t mode);
  static at::Tensor empty(at::IntArrayRef size,
                          const at::TensorOptions &options,
                          c10::optional<at::MemoryFormat> memory_format);
  static at::Tensor new_empty(const at::Tensor &self, at::IntArrayRef size,
                              const at::TensorOptions &options);
  static at::Tensor new_full(const at::Tensor &self, at::IntArrayRef size,
                             at::Scalar fill_value,
                             const at::TensorOptions &options);
  static at::Tensor _empty_affine_quantized(
      at::IntArrayRef size, const at::TensorOptions &options, double scale,
      int64_t zero_point, c10::optional<at::MemoryFormat> memory_format);
  static at::Tensor _empty_per_channel_affine_quantized_like(
      const at::Tensor &self, const at::Tensor &zero_points,
      at::IntArrayRef size, at::IntArrayRef axis,
      const at::TensorOptions &options,
      c10::optional<at::MemoryFormat> memory_format);
  static at::Tensor &resize_(at::Tensor &self, at::IntArrayRef size);
  static at::Tensor &empty_out(at::Tensor &out, at::IntArrayRef size,
                               c10::optional<at::MemoryFormat> memory_format);
  static at::Tensor empty_like(const at::Tensor &self);
  static at::Tensor empty_like(const at::Tensor &self,
                               const at::TensorOptions &options,
                               c10::optional<at::MemoryFormat> memory_format);
  static at::Tensor empty_strided(at::IntArrayRef size, at::IntArrayRef stride,
                                  const at::TensorOptions &options);
  static at::Tensor erf(const at::Tensor &self);
  static at::Tensor &erf_(at::Tensor &self);
  static at::Tensor &erf_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor erfc(const at::Tensor &self);
  static at::Tensor &erfc_(at::Tensor &self);
  static at::Tensor &erfc_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor exp(const at::Tensor &self);
  static at::Tensor &exp_(at::Tensor &self);
  static at::Tensor &exp_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor expm1(const at::Tensor &self);
  static at::Tensor &expm1_(at::Tensor &self);
  static at::Tensor &expm1_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor expand(const at::Tensor &self, at::IntArrayRef size,
                           bool implicit);
  static at::Tensor expand_as(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor eye(int64_t n, const at::TensorOptions &options);
  static at::Tensor eye(int64_t n, int64_t m, const at::TensorOptions &options);
  static at::Tensor &eye_out(at::Tensor &out, int64_t n);
  static at::Tensor &eye_out(at::Tensor &out, int64_t n, int64_t m);
  static at::Tensor flatten(const at::Tensor &self, int64_t start_dim,
                            int64_t end_dim);
  static at::Tensor &fill_(at::Tensor &self, at::Scalar value);
  static at::Tensor &fill_(at::Tensor &self, const at::Tensor &value);
  static at::Tensor floor(const at::Tensor &self);
  static at::Tensor &floor_(at::Tensor &self);
  static at::Tensor &floor_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor frac(const at::Tensor &self);
  static at::Tensor &frac_(at::Tensor &self);
  static at::Tensor &frac_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor full(at::IntArrayRef size, at::Scalar fill_value,
                         const at::TensorOptions &options);
  static at::Tensor &full_out(at::Tensor &out, at::IntArrayRef size,
                              at::Scalar fill_value);
  static at::Tensor full_like(const at::Tensor &self, at::Scalar fill_value);
  static at::Tensor full_like(const at::Tensor &self, at::Scalar fill_value,
                              const at::TensorOptions &options);
  static at::Tensor from_file(std::string filename, c10::optional<bool> shared,
                              c10::optional<int64_t> size,
                              const at::TensorOptions &options);
  static at::Tensor grid_sampler(const at::Tensor &input,
                                 const at::Tensor &grid,
                                 int64_t interpolation_mode,
                                 int64_t padding_mode, bool align_corners);
  static at::Tensor grid_sampler_2d(const at::Tensor &input,
                                    const at::Tensor &grid,
                                    int64_t interpolation_mode,
                                    int64_t padding_mode, bool align_corners);
  static std::tuple<at::Tensor, at::Tensor>
  grid_sampler_2d_backward(const at::Tensor &grad_output,
                           const at::Tensor &input, const at::Tensor &grid,
                           int64_t interpolation_mode, int64_t padding_mode,
                           bool align_corners);
  static at::Tensor grid_sampler_3d(const at::Tensor &input,
                                    const at::Tensor &grid,
                                    int64_t interpolation_mode,
                                    int64_t padding_mode, bool align_corners);
  static std::tuple<at::Tensor, at::Tensor>
  grid_sampler_3d_backward(const at::Tensor &grad_output,
                           const at::Tensor &input, const at::Tensor &grid,
                           int64_t interpolation_mode, int64_t padding_mode,
                           bool align_corners);
  static at::Tensor hann_window(int64_t window_length,
                                const at::TensorOptions &options);
  static at::Tensor hann_window(int64_t window_length, bool periodic,
                                const at::TensorOptions &options);
  static at::Tensor hamming_window(int64_t window_length,
                                   const at::TensorOptions &options);
  static at::Tensor hamming_window(int64_t window_length, bool periodic,
                                   const at::TensorOptions &options);
  static at::Tensor hamming_window(int64_t window_length, bool periodic,
                                   double alpha,
                                   const at::TensorOptions &options);
  static at::Tensor hamming_window(int64_t window_length, bool periodic,
                                   double alpha, double beta,
                                   const at::TensorOptions &options);
  static at::Tensor hinge_embedding_loss(const at::Tensor &self,
                                         const at::Tensor &target,
                                         double margin, int64_t reduction);
  static at::Tensor ger(const at::Tensor &self, const at::Tensor &vec2);
  static at::Tensor &ger_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &vec2);
  static at::Tensor group_norm(const at::Tensor &input, int64_t num_groups,
                               const at::Tensor &weight, const at::Tensor &bias,
                               double eps, bool cudnn_enabled);
  static at::Tensor fft(const at::Tensor &self, int64_t signal_ndim,
                        bool normalized);
  static at::Tensor ifft(const at::Tensor &self, int64_t signal_ndim,
                         bool normalized);
  static at::Tensor rfft(const at::Tensor &self, int64_t signal_ndim,
                         bool normalized, bool onesided);
  static at::Tensor irfft(const at::Tensor &self, int64_t signal_ndim,
                          bool normalized, bool onesided,
                          at::IntArrayRef signal_sizes);
  static at::Tensor _fft_with_size(const at::Tensor &self, int64_t signal_ndim,
                                   bool complex_input, bool complex_output,
                                   bool inverse,
                                   at::IntArrayRef checked_signal_sizes,
                                   bool normalized, bool onesided,
                                   at::IntArrayRef output_sizes);
  static int64_t _cufft_get_plan_cache_size(int64_t device_index);
  static int64_t _cufft_get_plan_cache_max_size(int64_t device_index);
  static void _cufft_set_plan_cache_max_size(int64_t device_index,
                                             int64_t max_size);
  static void _cufft_clear_plan_cache(int64_t device_index);
  static at::Tensor index(const at::Tensor &self, at::TensorList indices);
  static at::Tensor &index_copy_(at::Tensor &self, int64_t dim,
                                 const at::Tensor &index,
                                 const at::Tensor &source);
  static at::Tensor index_copy(const at::Tensor &self, int64_t dim,
                               const at::Tensor &index,
                               const at::Tensor &source);
  static at::Tensor &index_put_(at::Tensor &self, at::TensorList indices,
                                const at::Tensor &values, bool accumulate);
  static at::Tensor index_put(const at::Tensor &self, at::TensorList indices,
                              const at::Tensor &values, bool accumulate);
  static at::Tensor &_index_put_impl_(at::Tensor &self, at::TensorList indices,
                                      const at::Tensor &values, bool accumulate,
                                      bool unsafe);
  static at::Tensor
  instance_norm(const at::Tensor &input, const at::Tensor &weight,
                const at::Tensor &bias, const at::Tensor &running_mean,
                const at::Tensor &running_var, bool use_input_stats,
                double momentum, double eps, bool cudnn_enabled);
  static at::Tensor inverse(const at::Tensor &self);
  static at::Tensor &inverse_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor _inverse_helper(const at::Tensor &self);
  static at::Tensor isclose(const at::Tensor &self, const at::Tensor &other,
                            double rtol, double atol, bool equal_nan);
  static at::Tensor isnan(const at::Tensor &self);
  static bool is_distributed(const at::Tensor &self);
  static bool is_floating_point(const at::Tensor &self);
  static bool is_complex(const at::Tensor &self);
  static bool is_nonzero(const at::Tensor &self);
  static bool is_same_size(const at::Tensor &self, const at::Tensor &other);
  static bool is_signed(const at::Tensor &self);
  static at::Tensor kl_div(const at::Tensor &self, const at::Tensor &target,
                           int64_t reduction);
  static at::Tensor kl_div_backward(const at::Tensor &grad_output,
                                    const at::Tensor &self,
                                    const at::Tensor &target,
                                    int64_t reduction);
  static std::tuple<at::Tensor, at::Tensor>
  kthvalue(const at::Tensor &self, int64_t k, int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  kthvalue_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
               int64_t k, int64_t dim, bool keepdim);
  static at::Tensor layer_norm(const at::Tensor &input,
                               at::IntArrayRef normalized_shape,
                               const at::Tensor &weight, const at::Tensor &bias,
                               double eps, bool cudnn_enable);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  native_layer_norm(const at::Tensor &input, const at::Tensor &weight,
                    const at::Tensor &bias, int64_t M, int64_t N, double eps);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  native_layer_norm_backward(const at::Tensor &grad_out,
                             const at::Tensor &input, const at::Tensor &mean,
                             const at::Tensor &rstd, const at::Tensor &weight,
                             int64_t M, int64_t N,
                             std::array<bool, 3> output_mask);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  native_layer_norm_double_backward(
      const at::Tensor &ggI, const at::Tensor &ggW, const at::Tensor &ggb,
      const at::Tensor &gO, const at::Tensor &input, const at::Tensor &mean,
      const at::Tensor &rstd, const at::Tensor &weight, int64_t M, int64_t N,
      std::array<bool, 3> output_mask);
  static at::Tensor linear(const at::Tensor &input, const at::Tensor &weight,
                           const at::Tensor &bias);
  static at::Tensor mkldnn_linear(const at::Tensor &input,
                                  const at::Tensor &weight,
                                  const at::Tensor &bias);
  static at::Tensor fbgemm_linear_int8_weight_fp32_activation(
      const at::Tensor &input, const at::Tensor &weight,
      const at::Tensor &packed, const at::Tensor &col_offsets,
      at::Scalar weight_scale, at::Scalar weight_zero_point,
      const at::Tensor &bias);
  static at::Tensor fbgemm_linear_int8_weight(const at::Tensor &input,
                                              const at::Tensor &weight,
                                              const at::Tensor &packed,
                                              const at::Tensor &col_offsets,
                                              at::Scalar weight_scale,
                                              at::Scalar weight_zero_point,
                                              const at::Tensor &bias);
  static std::tuple<at::Tensor, at::Tensor, double, int64_t>
  fbgemm_linear_quantize_weight(const at::Tensor &input);
  static at::Tensor fbgemm_pack_gemm_matrix_fp16(const at::Tensor &input);
  static at::Tensor
  fbgemm_linear_fp16_weight_fp32_activation(const at::Tensor &input,
                                            const at::Tensor &packed_weight,
                                            const at::Tensor &bias);
  static at::Tensor fbgemm_linear_fp16_weight(const at::Tensor &input,
                                              const at::Tensor &packed_weight,
                                              const at::Tensor &bias);
  static at::Tensor fbgemm_pack_quantized_matrix(const at::Tensor &input);
  static at::Tensor fbgemm_pack_quantized_matrix(const at::Tensor &input,
                                                 int64_t K, int64_t N);
  static at::Tensor linspace(at::Scalar start, at::Scalar end, int64_t steps,
                             const at::TensorOptions &options);
  static at::Tensor &linspace_out(at::Tensor &out, at::Scalar start,
                                  at::Scalar end, int64_t steps);
  static at::Tensor log(const at::Tensor &self);
  static at::Tensor &log_(at::Tensor &self);
  static at::Tensor &log_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor log10(const at::Tensor &self);
  static at::Tensor &log10_(at::Tensor &self);
  static at::Tensor &log10_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor log1p(const at::Tensor &self);
  static at::Tensor &log1p_(at::Tensor &self);
  static at::Tensor &log1p_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor log2(const at::Tensor &self);
  static at::Tensor &log2_(at::Tensor &self);
  static at::Tensor &log2_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor logdet(const at::Tensor &self);
  static at::Tensor logspace(at::Scalar start, at::Scalar end, int64_t steps,
                             double base, const at::TensorOptions &options);
  static at::Tensor &logspace_out(at::Tensor &out, at::Scalar start,
                                  at::Scalar end, int64_t steps, double base);
  static at::Tensor log_softmax(const at::Tensor &self, int64_t dim,
                                c10::optional<at::ScalarType> dtype);
  static at::Tensor _log_softmax(const at::Tensor &self, int64_t dim,
                                 bool half_to_float);
  static at::Tensor _log_softmax_backward_data(const at::Tensor &grad_output,
                                               const at::Tensor &output,
                                               int64_t dim,
                                               const at::Tensor &self);
  static at::Tensor logsumexp(const at::Tensor &self, at::IntArrayRef dim,
                              bool keepdim);
  static at::Tensor &logsumexp_out(at::Tensor &out, const at::Tensor &self,
                                   at::IntArrayRef dim, bool keepdim);
  static at::Tensor margin_ranking_loss(const at::Tensor &input1,
                                        const at::Tensor &input2,
                                        const at::Tensor &target, double margin,
                                        int64_t reduction);
  static at::Tensor matmul(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &matmul_out(at::Tensor &out, const at::Tensor &self,
                                const at::Tensor &other);
  static at::Tensor matrix_rank(const at::Tensor &self, double tol,
                                bool symmetric);
  static at::Tensor matrix_rank(const at::Tensor &self, bool symmetric);
  static at::Tensor matrix_power(const at::Tensor &self, int64_t n);
  static std::tuple<at::Tensor, at::Tensor> max(const at::Tensor &self,
                                                int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  max_out(at::Tensor &max, at::Tensor &max_values, const at::Tensor &self,
          int64_t dim, bool keepdim);
  static at::Tensor max_values(const at::Tensor &self, at::IntArrayRef dim,
                               bool keepdim);
  static std::tuple<at::Tensor, at::Tensor>
  max_pool1d_with_indices(const at::Tensor &self, at::IntArrayRef kernel_size,
                          at::IntArrayRef stride, at::IntArrayRef padding,
                          at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor max_pool1d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor max_pool2d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor mkldnn_max_pool2d(const at::Tensor &self,
                                      at::IntArrayRef kernel_size,
                                      at::IntArrayRef stride,
                                      at::IntArrayRef padding,
                                      at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor quantized_max_pool2d(const at::Tensor &self,
                                         at::IntArrayRef kernel_size,
                                         at::IntArrayRef stride,
                                         at::IntArrayRef padding,
                                         at::IntArrayRef dilation);
  static at::Tensor max_pool3d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor mean(const at::Tensor &self,
                         c10::optional<at::ScalarType> dtype);
  static at::Tensor mean(const at::Tensor &self, at::IntArrayRef dim,
                         bool keepdim, c10::optional<at::ScalarType> dtype);
  static at::Tensor &mean_out(at::Tensor &out, const at::Tensor &self,
                              at::IntArrayRef dim, bool keepdim,
                              c10::optional<at::ScalarType> dtype);
  static std::tuple<at::Tensor, at::Tensor> median(const at::Tensor &self,
                                                   int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  median_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
             int64_t dim, bool keepdim);
  static std::tuple<at::Tensor, at::Tensor> min(const at::Tensor &self,
                                                int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  min_out(at::Tensor &min, at::Tensor &min_indices, const at::Tensor &self,
          int64_t dim, bool keepdim);
  static at::Tensor min_values(const at::Tensor &self, at::IntArrayRef dim,
                               bool keepdim);
  static at::Tensor
  mkldnn_convolution(const at::Tensor &self, const at::Tensor &weight,
                     const at::Tensor &bias, at::IntArrayRef padding,
                     at::IntArrayRef stride, at::IntArrayRef dilation,
                     int64_t groups);
  static at::Tensor mkldnn_convolution_backward_input(
      at::IntArrayRef self_size, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool bias_defined);
  static std::tuple<at::Tensor, at::Tensor> mkldnn_convolution_backward_weights(
      at::IntArrayRef weight_size, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool bias_defined);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  mkldnn_convolution_backward(const at::Tensor &self,
                              const at::Tensor &grad_output,
                              const at::Tensor &weight, at::IntArrayRef padding,
                              at::IntArrayRef stride, at::IntArrayRef dilation,
                              int64_t groups, std::array<bool, 3> output_mask);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  miopen_batch_norm(const at::Tensor &input, const at::Tensor &weight,
                    const at::Tensor &bias, const at::Tensor &running_mean,
                    const at::Tensor &running_var, bool training,
                    double exponential_average_factor, double epsilon);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  miopen_batch_norm_backward(const at::Tensor &input,
                             const at::Tensor &grad_output,
                             const at::Tensor &weight,
                             const at::Tensor &running_mean,
                             const at::Tensor &running_var,
                             const at::Tensor &save_mean,
                             const at::Tensor &save_var, double epsilon);
  static at::Tensor
  miopen_convolution(const at::Tensor &self, const at::Tensor &weight,
                     const at::Tensor &bias, at::IntArrayRef padding,
                     at::IntArrayRef stride, at::IntArrayRef dilation,
                     int64_t groups, bool benchmark, bool deterministic);
  static at::Tensor miopen_convolution_backward_input(
      at::IntArrayRef self_size, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  miopen_convolution_backward(const at::Tensor &self,
                              const at::Tensor &grad_output,
                              const at::Tensor &weight, at::IntArrayRef padding,
                              at::IntArrayRef stride, at::IntArrayRef dilation,
                              int64_t groups, bool benchmark,
                              bool deterministic,
                              std::array<bool, 3> output_mask);
  static at::Tensor
  miopen_convolution_backward_bias(const at::Tensor &grad_output);
  static at::Tensor miopen_convolution_backward_weight(
      at::IntArrayRef weight_size, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic);
  static at::Tensor miopen_convolution_transpose(
      const at::Tensor &self, const at::Tensor &weight, const at::Tensor &bias,
      at::IntArrayRef padding, at::IntArrayRef output_padding,
      at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups,
      bool benchmark, bool deterministic);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  miopen_convolution_transpose_backward(
      const at::Tensor &self, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic, std::array<bool, 3> output_mask);
  static at::Tensor miopen_convolution_transpose_backward_input(
      const at::Tensor &grad_output, const at::Tensor &weight,
      at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation,
      int64_t groups, bool benchmark, bool deterministic);
  static at::Tensor miopen_convolution_transpose_backward_weight(
      at::IntArrayRef weight_size, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic);
  static at::Tensor miopen_depthwise_convolution(
      const at::Tensor &self, const at::Tensor &weight, const at::Tensor &bias,
      at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation,
      int64_t groups, bool benchmark, bool deterministic);
  static at::Tensor miopen_depthwise_convolution_backward_input(
      at::IntArrayRef self_size, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  miopen_depthwise_convolution_backward(
      const at::Tensor &self, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic, std::array<bool, 3> output_mask);
  static at::Tensor miopen_depthwise_convolution_backward_weight(
      at::IntArrayRef weight_size, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding, at::IntArrayRef stride,
      at::IntArrayRef dilation, int64_t groups, bool benchmark,
      bool deterministic);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  miopen_rnn(const at::Tensor &input, at::TensorList weight,
             int64_t weight_stride0, const at::Tensor &hx, const at::Tensor &cx,
             int64_t mode, int64_t hidden_size, int64_t num_layers,
             bool batch_first, double dropout, bool train, bool bidirectional,
             at::IntArrayRef batch_sizes, const at::Tensor &dropout_state);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, std::vector<at::Tensor>>
  miopen_rnn_backward(const at::Tensor &input, at::TensorList weight,
                      int64_t weight_stride0, const at::Tensor &weight_buf,
                      const at::Tensor &hx, const at::Tensor &cx,
                      const at::Tensor &output, const at::Tensor &grad_output,
                      const at::Tensor &grad_hy, const at::Tensor &grad_cy,
                      int64_t mode, int64_t hidden_size, int64_t num_layers,
                      bool batch_first, double dropout, bool train,
                      bool bidirectional, at::IntArrayRef batch_sizes,
                      const at::Tensor &dropout_state,
                      const at::Tensor &reserve,
                      std::array<bool, 4> output_mask);
  static at::Tensor mm(const at::Tensor &self, const at::Tensor &mat2);
  static at::Tensor &mm_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &mat2);
  static at::Tensor _sparse_mm(const at::Tensor &sparse,
                               const at::Tensor &dense);
  static std::tuple<at::Tensor, at::Tensor> mode(const at::Tensor &self,
                                                 int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  mode_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
           int64_t dim, bool keepdim);
  static at::Tensor mul(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &mul_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &mul_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other);
  static at::Tensor mul(const at::Tensor &self, at::Scalar other);
  static at::Tensor &mul_(at::Tensor &self, at::Scalar other);
  static at::Tensor mv(const at::Tensor &self, const at::Tensor &vec);
  static at::Tensor &mv_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &vec);
  static at::Tensor mvlgamma(const at::Tensor &self, int64_t p);
  static at::Tensor &mvlgamma_(at::Tensor &self, int64_t p);
  static at::Tensor narrow_copy(const at::Tensor &self, int64_t dim,
                                int64_t start, int64_t length);
  static at::Tensor narrow(const at::Tensor &self, int64_t dim, int64_t start,
                           int64_t length);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  native_batch_norm(const at::Tensor &input, const at::Tensor &weight,
                    const at::Tensor &bias, const at::Tensor &running_mean,
                    const at::Tensor &running_var, bool training,
                    double momentum, double eps);
  static std::tuple<at::Tensor, at::Tensor>
  batch_norm_stats(const at::Tensor &input, double eps);
  static at::Tensor batch_norm_elemt(const at::Tensor &input,
                                     const at::Tensor &weight,
                                     const at::Tensor &bias,
                                     const at::Tensor &mean,
                                     const at::Tensor &invstd, double eps);
  static std::tuple<at::Tensor, at::Tensor> batch_norm_gather_stats(
      const at::Tensor &input, const at::Tensor &mean, const at::Tensor &invstd,
      const at::Tensor &running_mean, const at::Tensor &running_var,
      double momentum, double eps, int64_t count);
  static std::tuple<at::Tensor, at::Tensor> batch_norm_gather_stats_with_counts(
      const at::Tensor &input, const at::Tensor &mean, const at::Tensor &invstd,
      const at::Tensor &running_mean, const at::Tensor &running_var,
      double momentum, double eps, at::IntArrayRef counts);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  native_batch_norm_backward(const at::Tensor &grad_out,
                             const at::Tensor &input, const at::Tensor &weight,
                             const at::Tensor &running_mean,
                             const at::Tensor &running_var,
                             const at::Tensor &save_mean,
                             const at::Tensor &save_invstd, bool train,
                             double eps, std::array<bool, 3> output_mask);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  batch_norm_backward_reduce(const at::Tensor &grad_out,
                             const at::Tensor &input, const at::Tensor &mean,
                             const at::Tensor &invstd, const at::Tensor &weight,
                             bool input_g, bool weight_g, bool bias_g);
  static at::Tensor
  batch_norm_backward_elemt(const at::Tensor &grad_out, const at::Tensor &input,
                            const at::Tensor &mean, const at::Tensor &invstd,
                            const at::Tensor &weight, const at::Tensor &mean_dy,
                            const at::Tensor &mean_dy_xmu);
  static std::tuple<at::Tensor, at::Tensor>
  batch_norm_update_stats(const at::Tensor &input,
                          const at::Tensor &running_mean,
                          const at::Tensor &running_var, double momentum);
  static at::Tensor _nnpack_spatial_convolution(const at::Tensor &input,
                                                const at::Tensor &weight,
                                                const at::Tensor &bias,
                                                at::IntArrayRef padding);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _nnpack_spatial_convolution_backward(const at::Tensor &input,
                                       const at::Tensor &grad_output,
                                       const at::Tensor &weight,
                                       at::IntArrayRef padding,
                                       std::array<bool, 3> output_mask);
  static at::Tensor _nnpack_spatial_convolution_backward_input(
      const at::Tensor &input, const at::Tensor &grad_output,
      const at::Tensor &weight, at::IntArrayRef padding);
  static at::Tensor _nnpack_spatial_convolution_backward_weight(
      const at::Tensor &input, at::IntArrayRef weightsize,
      const at::Tensor &grad_output, at::IntArrayRef padding);
  static at::Tensor &ones_out(at::Tensor &out, at::IntArrayRef size);
  static at::Tensor pairwise_distance(const at::Tensor &x1,
                                      const at::Tensor &x2, double p,
                                      double eps, bool keepdim);
  static at::Tensor cdist(const at::Tensor &x1, const at::Tensor &x2, double p);
  static at::Tensor _cdist_backward(const at::Tensor &grad,
                                    const at::Tensor &x1, const at::Tensor &x2,
                                    double p, const at::Tensor &cdist);
  static at::Tensor pdist(const at::Tensor &self, double p);
  static at::Tensor _pdist_forward(const at::Tensor &self, double p);
  static at::Tensor _pdist_backward(const at::Tensor &grad,
                                    const at::Tensor &self, double p,
                                    const at::Tensor &pdist);
  static at::Tensor cosine_similarity(const at::Tensor &x1,
                                      const at::Tensor &x2, int64_t dim,
                                      double eps);
  static at::Tensor permute(const at::Tensor &self, at::IntArrayRef dims);
  static at::Tensor numpy_T(const at::Tensor &self);
  static at::Tensor pixel_shuffle(const at::Tensor &self,
                                  int64_t upscale_factor);
  static bool is_pinned(const at::Tensor &self);
  static at::Tensor pin_memory(const at::Tensor &self);
  static at::Tensor pinverse(const at::Tensor &self, double rcond);
  static at::Tensor poisson_nll_loss(const at::Tensor &input,
                                     const at::Tensor &target, bool log_input,
                                     bool full, double eps, int64_t reduction);
  static at::Tensor scalar_tensor(at::Scalar s,
                                  const at::TensorOptions &options);
  static at::Tensor rand(at::IntArrayRef size,
                         const at::TensorOptions &options);
  static at::Tensor rand(at::IntArrayRef size, at::Generator *generator,
                         const at::TensorOptions &options);
  static at::Tensor &rand_out(at::Tensor &out, at::IntArrayRef size);
  static at::Tensor &rand_out(at::Tensor &out, at::IntArrayRef size,
                              at::Generator *generator);
  static at::Tensor rand_like(const at::Tensor &self);
  static at::Tensor rand_like(const at::Tensor &self,
                              const at::TensorOptions &options);
  static at::Tensor randint(int64_t high, at::IntArrayRef size,
                            const at::TensorOptions &options);
  static at::Tensor randint(int64_t high, at::IntArrayRef size,
                            at::Generator *generator,
                            const at::TensorOptions &options);
  static at::Tensor randint(int64_t low, int64_t high, at::IntArrayRef size,
                            const at::TensorOptions &options);
  static at::Tensor randint(int64_t low, int64_t high, at::IntArrayRef size,
                            at::Generator *generator,
                            const at::TensorOptions &options);
  static at::Tensor &randint_out(at::Tensor &out, int64_t high,
                                 at::IntArrayRef size);
  static at::Tensor &randint_out(at::Tensor &out, int64_t high,
                                 at::IntArrayRef size,
                                 at::Generator *generator);
  static at::Tensor &randint_out(at::Tensor &out, int64_t low, int64_t high,
                                 at::IntArrayRef size);
  static at::Tensor &randint_out(at::Tensor &out, int64_t low, int64_t high,
                                 at::IntArrayRef size,
                                 at::Generator *generator);
  static at::Tensor randint_like(const at::Tensor &self, int64_t high);
  static at::Tensor randint_like(const at::Tensor &self, int64_t low,
                                 int64_t high);
  static at::Tensor randint_like(const at::Tensor &self, int64_t high,
                                 const at::TensorOptions &options);
  static at::Tensor randint_like(const at::Tensor &self, int64_t low,
                                 int64_t high,
                                 const at::TensorOptions &options);
  static at::Tensor randn(at::IntArrayRef size,
                          const at::TensorOptions &options);
  static at::Tensor randn(at::IntArrayRef size, at::Generator *generator,
                          const at::TensorOptions &options);
  static at::Tensor &randn_out(at::Tensor &out, at::IntArrayRef size);
  static at::Tensor &randn_out(at::Tensor &out, at::IntArrayRef size,
                               at::Generator *generator);
  static at::Tensor randn_like(const at::Tensor &self);
  static at::Tensor randn_like(const at::Tensor &self,
                               const at::TensorOptions &options);
  static at::Tensor randperm(int64_t n, const at::TensorOptions &options);
  static at::Tensor randperm(int64_t n, at::Generator *generator,
                             const at::TensorOptions &options);
  static at::Tensor &randperm_out(at::Tensor &out, int64_t n);
  static at::Tensor &randperm_out(at::Tensor &out, int64_t n,
                                  at::Generator *generator);
  static at::Tensor range(at::Scalar start, at::Scalar end, at::Scalar step,
                          const at::TensorOptions &options);
  static at::Tensor range(at::Scalar start, at::Scalar end,
                          const at::TensorOptions &options);
  static at::Tensor &range_out(at::Tensor &out, at::Scalar start,
                               at::Scalar end, at::Scalar step);
  static at::Tensor reciprocal(const at::Tensor &self);
  static at::Tensor &reciprocal_(at::Tensor &self);
  static at::Tensor &reciprocal_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor neg(const at::Tensor &self);
  static at::Tensor &neg_(at::Tensor &self);
  static at::Tensor &neg_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor repeat(const at::Tensor &self, at::IntArrayRef repeats);
  static at::Tensor repeat_interleave(const at::Tensor &repeats);
  static at::Tensor repeat_interleave(const at::Tensor &self,
                                      const at::Tensor &repeats,
                                      c10::optional<int64_t> dim);
  static at::Tensor repeat_interleave(const at::Tensor &self, int64_t repeats,
                                      c10::optional<int64_t> dim);
  static at::Tensor reshape(const at::Tensor &self, at::IntArrayRef shape);
  static at::Tensor _mkldnn_reshape(const at::Tensor &self,
                                    at::IntArrayRef shape);
  static at::Tensor reshape_as(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor round(const at::Tensor &self);
  static at::Tensor &round_(at::Tensor &self);
  static at::Tensor &round_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor rrelu(const at::Tensor &self, at::Scalar lower,
                          at::Scalar upper, bool training,
                          at::Generator *generator);
  static at::Tensor &rrelu_(at::Tensor &self, at::Scalar lower,
                            at::Scalar upper, bool training,
                            at::Generator *generator);
  static at::Tensor relu(const at::Tensor &self);
  static at::Tensor &relu_(at::Tensor &self);
  static at::Tensor prelu(const at::Tensor &self, const at::Tensor &weight);
  static std::tuple<at::Tensor, at::Tensor>
  prelu_backward(const at::Tensor &grad_output, const at::Tensor &self,
                 const at::Tensor &weight);
  static at::Tensor gelu(const at::Tensor &self);
  static at::Tensor gelu_backward(const at::Tensor &grad,
                                  const at::Tensor &self);
  static at::Tensor hardshrink(const at::Tensor &self, at::Scalar lambd);
  static at::Tensor hardshrink_backward(const at::Tensor &grad_out,
                                        const at::Tensor &self,
                                        at::Scalar lambd);
  static at::Tensor rsqrt(const at::Tensor &self);
  static at::Tensor &rsqrt_(at::Tensor &self);
  static at::Tensor &rsqrt_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor select(const at::Tensor &self, int64_t dim, int64_t index);
  static at::Tensor selu(const at::Tensor &self);
  static at::Tensor &selu_(at::Tensor &self);
  static at::Tensor celu(const at::Tensor &self, at::Scalar alpha);
  static at::Tensor &celu_(at::Tensor &self, at::Scalar alpha);
  static at::Tensor sigmoid(const at::Tensor &self);
  static at::Tensor &sigmoid_(at::Tensor &self);
  static at::Tensor &sigmoid_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor sin(const at::Tensor &self);
  static at::Tensor &sin_(at::Tensor &self);
  static at::Tensor &sin_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor sinh(const at::Tensor &self);
  static at::Tensor &sinh_(at::Tensor &self);
  static at::Tensor &sinh_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor detach(const at::Tensor &self);
  static at::Tensor &detach_(at::Tensor &self);
  static int64_t size(const at::Tensor &self, int64_t dim);
  static at::Tensor slice(const at::Tensor &self, int64_t dim, int64_t start,
                          int64_t end, int64_t step);
  static std::tuple<at::Tensor, at::Tensor> slogdet(const at::Tensor &self);
  static at::Tensor smm(const at::Tensor &self, const at::Tensor &mat2);
  static at::Tensor softmax(const at::Tensor &self, int64_t dim,
                            c10::optional<at::ScalarType> dtype);
  static at::Tensor _softmax(const at::Tensor &self, int64_t dim,
                             bool half_to_float);
  static at::Tensor _softmax_backward_data(const at::Tensor &grad_output,
                                           const at::Tensor &output,
                                           int64_t dim, const at::Tensor &self);
  static at::Tensor &_sparse_add_out(at::Tensor &out, const at::Tensor &self,
                                     const at::Tensor &other, at::Scalar alpha);
  static at::Tensor &_sparse_dense_add_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           const at::Tensor &other,
                                           at::Scalar alpha);
  static at::Tensor &_sparse_div_zerodim_out(at::Tensor &out,
                                             const at::Tensor &self,
                                             const at::Tensor &other);
  static at::Tensor &_sparse_div_scalar_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::Scalar other);
  static at::Tensor &_sparse_mul_out(at::Tensor &out, const at::Tensor &self,
                                     const at::Tensor &other);
  static at::Tensor &_sparse_mul_zerodim_out(at::Tensor &out,
                                             const at::Tensor &self,
                                             const at::Tensor &other);
  static at::Tensor &_sparse_mul_scalar_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::Scalar other);
  static std::vector<at::Tensor> split(const at::Tensor &self,
                                       int64_t split_size, int64_t dim);
  static std::vector<at::Tensor> split_with_sizes(const at::Tensor &self,
                                                  at::IntArrayRef split_sizes,
                                                  int64_t dim);
  static at::Tensor squeeze(const at::Tensor &self);
  static at::Tensor squeeze(const at::Tensor &self, int64_t dim);
  static at::Tensor &squeeze_(at::Tensor &self);
  static at::Tensor &squeeze_(at::Tensor &self, int64_t dim);
  static at::Tensor sspaddmm(const at::Tensor &self, const at::Tensor &mat1,
                             const at::Tensor &mat2, at::Scalar beta,
                             at::Scalar alpha);
  static at::Tensor &sspaddmm_out(at::Tensor &out, const at::Tensor &self,
                                  const at::Tensor &mat1,
                                  const at::Tensor &mat2, at::Scalar beta,
                                  at::Scalar alpha);
  static at::Tensor stack(at::TensorList tensors, int64_t dim);
  static at::Tensor &stack_out(at::Tensor &out, at::TensorList tensors,
                               int64_t dim);
  static at::Tensor stft(const at::Tensor &self, int64_t n_fft,
                         c10::optional<int64_t> hop_length,
                         c10::optional<int64_t> win_length,
                         const at::Tensor &window, bool normalized,
                         bool onesided);
  static int64_t stride(const at::Tensor &self, int64_t dim);
  static at::Tensor sum(const at::Tensor &self,
                        c10::optional<at::ScalarType> dtype);
  static at::Tensor sum(const at::Tensor &self, at::IntArrayRef dim,
                        bool keepdim, c10::optional<at::ScalarType> dtype);
  static at::Tensor &sum_out(at::Tensor &out, const at::Tensor &self,
                             at::IntArrayRef dim, bool keepdim,
                             c10::optional<at::ScalarType> dtype);
  static at::Tensor sum_to_size(const at::Tensor &self, at::IntArrayRef size);
  static at::Tensor sqrt(const at::Tensor &self);
  static at::Tensor &sqrt_(at::Tensor &self);
  static at::Tensor &sqrt_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor std(const at::Tensor &self, bool unbiased);
  static at::Tensor std(const at::Tensor &self, at::IntArrayRef dim,
                        bool unbiased, bool keepdim);
  static std::tuple<at::Tensor, at::Tensor> std_mean(const at::Tensor &self,
                                                     bool unbiased);
  static std::tuple<at::Tensor, at::Tensor> std_mean(const at::Tensor &self,
                                                     at::IntArrayRef dim,
                                                     bool unbiased,
                                                     bool keepdim);
  static at::Tensor &std_out(at::Tensor &out, const at::Tensor &self,
                             at::IntArrayRef dim, bool unbiased, bool keepdim);
  static at::Tensor prod(const at::Tensor &self,
                         c10::optional<at::ScalarType> dtype);
  static at::Tensor prod(const at::Tensor &self, int64_t dim, bool keepdim,
                         c10::optional<at::ScalarType> dtype);
  static at::Tensor &prod_out(at::Tensor &out, const at::Tensor &self,
                              int64_t dim, bool keepdim,
                              c10::optional<at::ScalarType> dtype);
  static at::Tensor t(const at::Tensor &self);
  static at::Tensor &t_(at::Tensor &self);
  static at::Tensor tan(const at::Tensor &self);
  static at::Tensor &tan_(at::Tensor &self);
  static at::Tensor &tan_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor tanh(const at::Tensor &self);
  static at::Tensor &tanh_(at::Tensor &self);
  static at::Tensor &tanh_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor tensordot(const at::Tensor &self, const at::Tensor &other,
                              at::IntArrayRef dims_self,
                              at::IntArrayRef dims_other);
  static at::Tensor threshold(const at::Tensor &self, at::Scalar threshold,
                              at::Scalar value);
  static at::Tensor &threshold_(at::Tensor &self, at::Scalar threshold,
                                at::Scalar value);
  static at::Tensor &threshold_out(at::Tensor &out, const at::Tensor &self,
                                   at::Scalar threshold, at::Scalar value);
  static at::Tensor threshold_backward(const at::Tensor &grad_output,
                                       const at::Tensor &self,
                                       at::Scalar threshold);
  static at::Tensor transpose(const at::Tensor &self, int64_t dim0,
                              int64_t dim1);
  static at::Tensor _mkldnn_transpose(const at::Tensor &self, int64_t dim0,
                                      int64_t dim1);
  static at::Tensor &transpose_(at::Tensor &self, int64_t dim0, int64_t dim1);
  static at::Tensor &_mkldnn_transpose_(at::Tensor &self, int64_t dim0,
                                        int64_t dim1);
  static at::Tensor one_hot(const at::Tensor &self, int64_t num_classes);
  static at::Tensor flip(const at::Tensor &self, at::IntArrayRef dims);
  static at::Tensor roll(const at::Tensor &self, at::IntArrayRef shifts,
                         at::IntArrayRef dims);
  static at::Tensor rot90(const at::Tensor &self, int64_t k,
                          at::IntArrayRef dims);
  static at::Tensor trapz(const at::Tensor &y, const at::Tensor &x,
                          int64_t dim);
  static at::Tensor trapz(const at::Tensor &y, double dx, int64_t dim);
  static at::Tensor _trilinear(const at::Tensor &i1, const at::Tensor &i2,
                               const at::Tensor &i3, at::IntArrayRef expand1,
                               at::IntArrayRef expand2, at::IntArrayRef expand3,
                               at::IntArrayRef sumdim, int64_t unroll_dim);
  static at::Tensor triplet_margin_loss(const at::Tensor &anchor,
                                        const at::Tensor &positive,
                                        const at::Tensor &negative,
                                        double margin, double p, double eps,
                                        bool swap, int64_t reduction);
  static at::Tensor trunc(const at::Tensor &self);
  static at::Tensor &trunc_(at::Tensor &self);
  static at::Tensor &trunc_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor type_as(const at::Tensor &self, const at::Tensor &other);
  static bool _has_compatible_shallow_copy_type(const at::Tensor &self,
                                                const at::Tensor &from);
  static std::tuple<at::Tensor, at::Tensor>
  _unique(const at::Tensor &self, bool sorted, bool return_inverse);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  unique_dim(const at::Tensor &self, int64_t dim, bool sorted,
             bool return_inverse, bool return_counts);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  unique_consecutive(const at::Tensor &self, bool return_inverse,
                     bool return_counts, c10::optional<int64_t> dim);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  unique_dim_consecutive(const at::Tensor &self, int64_t dim,
                         bool return_inverse, bool return_counts);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _unique2(const at::Tensor &self, bool sorted, bool return_inverse,
           bool return_counts);
  static at::Tensor _unsafe_view(const at::Tensor &self, at::IntArrayRef size);
  static at::Tensor unsqueeze(const at::Tensor &self, int64_t dim);
  static at::Tensor &unsqueeze_(at::Tensor &self, int64_t dim);
  static at::Tensor var(const at::Tensor &self, bool unbiased);
  static at::Tensor var(const at::Tensor &self, at::IntArrayRef dim,
                        bool unbiased, bool keepdim);
  static at::Tensor &var_out(at::Tensor &out, const at::Tensor &self,
                             at::IntArrayRef dim, bool unbiased, bool keepdim);
  static std::tuple<at::Tensor, at::Tensor> var_mean(const at::Tensor &self,
                                                     bool unbiased);
  static std::tuple<at::Tensor, at::Tensor> var_mean(const at::Tensor &self,
                                                     at::IntArrayRef dim,
                                                     bool unbiased,
                                                     bool keepdim);
  static at::Tensor view_as(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor where(const at::Tensor &condition, const at::Tensor &self,
                          const at::Tensor &other);
  static std::vector<at::Tensor> where(const at::Tensor &condition);
  static at::Tensor _s_where(const at::Tensor &condition,
                             const at::Tensor &self, const at::Tensor &other);
  static at::Tensor norm_except_dim(const at::Tensor &v, int64_t pow,
                                    int64_t dim);
  static at::Tensor _weight_norm(const at::Tensor &v, const at::Tensor &g,
                                 int64_t dim);
  static std::tuple<at::Tensor, at::Tensor>
  _weight_norm_cuda_interface(const at::Tensor &v, const at::Tensor &g,
                              int64_t dim);
  static std::tuple<at::Tensor, at::Tensor>
  _weight_norm_cuda_interface_backward(const at::Tensor &grad_w,
                                       const at::Tensor &saved_v,
                                       const at::Tensor &saved_g,
                                       const at::Tensor &saved_norms,
                                       int64_t dim);
  static std::tuple<at::Tensor, at::Tensor>
  _weight_norm_differentiable_backward(const at::Tensor &grad_w,
                                       const at::Tensor &saved_v,
                                       const at::Tensor &saved_g,
                                       const at::Tensor &saved_norms,
                                       int64_t dim);
  static at::Tensor &zeros_out(at::Tensor &out, at::IntArrayRef size);
  static at::Tensor _standard_gamma_grad(const at::Tensor &self,
                                         const at::Tensor &output);
  static at::Tensor _standard_gamma(const at::Tensor &self,
                                    at::Generator *generator);
  static at::Tensor _dirichlet_grad(const at::Tensor &x,
                                    const at::Tensor &alpha,
                                    const at::Tensor &total);
  static at::Tensor _sample_dirichlet(const at::Tensor &self,
                                      at::Generator *generator);
  static at::Tensor poisson(const at::Tensor &self, at::Generator *generator);
  static at::Tensor native_norm(const at::Tensor &self, at::Scalar p);
  static at::Tensor _sparse_sum(const at::Tensor &self);
  static at::Tensor _sparse_sum(const at::Tensor &self, at::ScalarType dtype);
  static at::Tensor _sparse_sum(const at::Tensor &self, at::IntArrayRef dim);
  static at::Tensor _sparse_sum(const at::Tensor &self, at::IntArrayRef dim,
                                at::ScalarType dtype);
  static at::Tensor _sparse_sum_backward(const at::Tensor &grad,
                                         const at::Tensor &self,
                                         at::IntArrayRef dim);
  static at::Tensor norm(const at::Tensor &self, c10::optional<at::Scalar> p,
                         at::ScalarType dtype);
  static at::Tensor norm(const at::Tensor &self, at::Scalar p);
  static at::Tensor norm(const at::Tensor &self, c10::optional<at::Scalar> p,
                         at::IntArrayRef dim, bool keepdim,
                         at::ScalarType dtype);
  static at::Tensor norm(const at::Tensor &self, c10::optional<at::Scalar> p,
                         at::IntArrayRef dim, bool keepdim);
  static at::Tensor &norm_out(at::Tensor &out, const at::Tensor &self,
                              c10::optional<at::Scalar> p, at::IntArrayRef dim,
                              bool keepdim, at::ScalarType dtype);
  static at::Tensor &norm_out(at::Tensor &out, const at::Tensor &self,
                              c10::optional<at::Scalar> p, at::IntArrayRef dim,
                              bool keepdim);
  static at::Tensor frobenius_norm(const at::Tensor &self);
  static at::Tensor frobenius_norm(const at::Tensor &self, at::IntArrayRef dim,
                                   bool keepdim);
  static at::Tensor &frobenius_norm_out(at::Tensor &out, const at::Tensor &self,
                                        at::IntArrayRef dim, bool keepdim);
  static at::Tensor nuclear_norm(const at::Tensor &self, bool keepdim);
  static at::Tensor &nuclear_norm_out(at::Tensor &out, const at::Tensor &self,
                                      bool keepdim);
  static at::Tensor nuclear_norm(const at::Tensor &self, at::IntArrayRef dim,
                                 bool keepdim);
  static at::Tensor &nuclear_norm_out(at::Tensor &out, const at::Tensor &self,
                                      at::IntArrayRef dim, bool keepdim);
  static at::Tensor clone(const at::Tensor &self);
  static at::Tensor &resize_as_(at::Tensor &self,
                                const at::Tensor &the_template);
  static at::Tensor &pow_out(at::Tensor &out, const at::Tensor &self,
                             at::Scalar exponent);
  static at::Tensor pow(const at::Tensor &self, at::Scalar exponent);
  static at::Tensor &zero_(at::Tensor &self);
  static at::Tensor &sub_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other, at::Scalar alpha);
  static at::Tensor sub(const at::Tensor &self, const at::Tensor &other,
                        at::Scalar alpha);
  static at::Tensor &sub_(at::Tensor &self, const at::Tensor &other,
                          at::Scalar alpha);
  static at::Tensor sub(const at::Tensor &self, at::Scalar other,
                        at::Scalar alpha);
  static at::Tensor &sub_(at::Tensor &self, at::Scalar other, at::Scalar alpha);
  static at::Tensor rsub(const at::Tensor &self, const at::Tensor &other,
                         at::Scalar alpha);
  static at::Tensor rsub(const at::Tensor &self, at::Scalar other,
                         at::Scalar alpha);
  static at::Tensor &s_native_addmm_out(at::Tensor &out, const at::Tensor &self,
                                        const at::Tensor &mat1,
                                        const at::Tensor &mat2, at::Scalar beta,
                                        at::Scalar alpha);
  static at::Tensor s_native_addmm(const at::Tensor &self,
                                   const at::Tensor &mat1,
                                   const at::Tensor &mat2, at::Scalar beta,
                                   at::Scalar alpha);
  static at::Tensor &s_native_addmm_(at::Tensor &self, const at::Tensor &mat1,
                                     const at::Tensor &mat2, at::Scalar beta,
                                     at::Scalar alpha);
  static at::Tensor _sparse_addmm(const at::Tensor &self,
                                  const at::Tensor &sparse,
                                  const at::Tensor &dense, at::Scalar beta,
                                  at::Scalar alpha);
  static at::Tensor &addmm_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &mat1, const at::Tensor &mat2,
                               at::Scalar beta, at::Scalar alpha);
  static at::Tensor addmm(const at::Tensor &self, const at::Tensor &mat1,
                          const at::Tensor &mat2, at::Scalar beta,
                          at::Scalar alpha);
  static at::Tensor &addmm_(at::Tensor &self, const at::Tensor &mat1,
                            const at::Tensor &mat2, at::Scalar beta,
                            at::Scalar alpha);
  static at::Tensor sparse_coo_tensor(at::IntArrayRef size,
                                      const at::TensorOptions &options);
  static at::Tensor sparse_coo_tensor(const at::Tensor &indices,
                                      const at::Tensor &values,
                                      const at::TensorOptions &options);
  static at::Tensor sparse_coo_tensor(const at::Tensor &indices,
                                      const at::Tensor &values,
                                      at::IntArrayRef size,
                                      const at::TensorOptions &options);
  static at::Tensor _sparse_coo_tensor_unsafe(const at::Tensor &indices,
                                              const at::Tensor &values,
                                              at::IntArrayRef size,
                                              const at::TensorOptions &options);
  static at::Tensor
  _sparse_coo_tensor_with_dims(int64_t sparse_dim, int64_t dense_dim,
                               at::IntArrayRef size,
                               const at::TensorOptions &options);
  static at::Tensor _sparse_coo_tensor_with_dims_and_tensors(
      int64_t sparse_dim, int64_t dense_dim, at::IntArrayRef size,
      const at::Tensor &indices, const at::Tensor &values,
      const at::TensorOptions &options);
  static at::Tensor &sparse_resize_(at::Tensor &self, at::IntArrayRef size,
                                    int64_t sparse_dim, int64_t dense_dim);
  static at::Tensor &sparse_resize_and_clear_(at::Tensor &self,
                                              at::IntArrayRef size,
                                              int64_t sparse_dim,
                                              int64_t dense_dim);
  static at::Tensor sparse_mask(const at::Tensor &self, const at::Tensor &mask);
  static at::Tensor to_dense(const at::Tensor &self);
  static at::Tensor to_dense_backward(const at::Tensor &grad,
                                      const at::Tensor &input);
  static int64_t sparse_dim(const at::Tensor &self);
  static int64_t _dimI(const at::Tensor &self);
  static int64_t dense_dim(const at::Tensor &self);
  static int64_t _dimV(const at::Tensor &self);
  static int64_t _nnz(const at::Tensor &self);
  static at::Tensor coalesce(const at::Tensor &self);
  static bool is_coalesced(const at::Tensor &self);
  static at::Tensor _indices(const at::Tensor &self);
  static at::Tensor _values(const at::Tensor &self);
  static at::Tensor &_coalesced_(at::Tensor &self, bool coalesced);
  static at::Tensor indices(const at::Tensor &self);
  static at::Tensor values(const at::Tensor &self);
  static at::Tensor &hspmm_out(at::Tensor &out, const at::Tensor &mat1,
                               const at::Tensor &mat2);
  static at::Tensor hspmm(const at::Tensor &mat1, const at::Tensor &mat2);
  static at::Tensor &copy_sparse_to_sparse_(at::Tensor &self,
                                            const at::Tensor &src,
                                            bool non_blocking);
  static std::vector<at::Tensor> unbind(const at::Tensor &self, int64_t dim);
  static at::Tensor to_sparse(const at::Tensor &self, int64_t sparse_dim);
  static at::Tensor to_sparse(const at::Tensor &self);
  static at::Tensor to_mkldnn(const at::Tensor &self);
  static at::Tensor mkldnn_reorder_conv2d_weight(const at::Tensor &self,
                                                 at::IntArrayRef padding,
                                                 at::IntArrayRef stride,
                                                 at::IntArrayRef dilation,
                                                 int64_t groups);
  static at::Tensor to_mkldnn_backward(const at::Tensor &grad,
                                       const at::Tensor &input);
  static at::Tensor quantize_linear(const at::Tensor &self, double scale,
                                    int64_t zero_point, at::ScalarType dtype);
  static at::Tensor quantize_linear_per_channel(const at::Tensor &self,
                                                const at::Tensor &scales,
                                                const at::Tensor &zero_points,
                                                at::IntArrayRef axis,
                                                at::ScalarType dtype);
  static at::Tensor dequantize(const at::Tensor &self);
  static at::Tensor _dequantize_linear(const at::Tensor &self, double scale,
                                       int64_t zero_point,
                                       at::ScalarType dtype);
  static double q_scale(const at::Tensor &self);
  static int64_t q_zero_point(const at::Tensor &self);
  static at::Tensor q_per_channel_scales(const at::Tensor &self);
  static at::Tensor q_per_channel_zero_points(const at::Tensor &self);
  static at::Tensor int_repr(const at::Tensor &self);
  static at::Tensor _per_tensor_affine_qtensor(const at::Tensor &self,
                                               double scale,
                                               int64_t zero_point);
  static at::Tensor _per_channel_affine_qtensor(const at::Tensor &self,
                                                const at::Tensor &scale,
                                                const at::Tensor &zero_point,
                                                at::IntArrayRef axis);
  static at::QScheme qscheme(const at::Tensor &self);
  static at::Tensor fake_quantize_per_tensor_affine(const at::Tensor &self,
                                                    double scale,
                                                    int64_t zero_point,
                                                    int64_t quant_min,
                                                    int64_t quant_max);
  static at::Tensor fake_quantize_per_tensor_affine_backward(
      const at::Tensor &grad, const at::Tensor &self, double scale,
      int64_t zero_point, int64_t quant_min, int64_t quant_max);
  static at::Tensor to(const at::Tensor &self, const at::TensorOptions &options,
                       bool non_blocking, bool copy);
  static at::Tensor to(const at::Tensor &self, c10::Device device,
                       at::ScalarType dtype, bool non_blocking, bool copy);
  static at::Tensor to(const at::Tensor &self, at::ScalarType dtype,
                       bool non_blocking, bool copy);
  static at::Tensor to(const at::Tensor &self, const at::Tensor &other,
                       bool non_blocking, bool copy);
  static std::vector<at::Tensor> meshgrid(at::TensorList tensors);
  static at::Tensor cartesian_prod(at::TensorList tensors);
  static at::Tensor combinations(const at::Tensor &self, int64_t r,
                                 bool with_replacement);
  static at::Scalar item(const at::Tensor &self);
  static at::Scalar _local_scalar_dense(const at::Tensor &self);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _thnn_fused_lstm_cell(const at::Tensor &input_gates,
                        const at::Tensor &hidden_gates, const at::Tensor &cx,
                        const at::Tensor &input_bias,
                        const at::Tensor &hidden_bias);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  _thnn_fused_lstm_cell_backward(const at::Tensor &grad_hy,
                                 const at::Tensor &grad_cy,
                                 const at::Tensor &cx, const at::Tensor &cy,
                                 const at::Tensor &workspace, bool has_bias);
  static std::tuple<at::Tensor, at::Tensor>
  _thnn_fused_gru_cell(const at::Tensor &input_gates,
                       const at::Tensor &hidden_gates, const at::Tensor &hx,
                       const at::Tensor &input_bias,
                       const at::Tensor &hidden_bias);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor, at::Tensor>
  _thnn_fused_gru_cell_backward(const at::Tensor &grad_hy,
                                const at::Tensor &workspace, bool has_bias);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  lstm(const at::Tensor &input, at::TensorList hx, at::TensorList params,
       bool has_biases, int64_t num_layers, double dropout, bool train,
       bool bidirectional, bool batch_first);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  lstm(const at::Tensor &data, const at::Tensor &batch_sizes, at::TensorList hx,
       at::TensorList params, bool has_biases, int64_t num_layers,
       double dropout, bool train, bool bidirectional);
  static std::tuple<at::Tensor, at::Tensor>
  gru(const at::Tensor &input, const at::Tensor &hx, at::TensorList params,
      bool has_biases, int64_t num_layers, double dropout, bool train,
      bool bidirectional, bool batch_first);
  static std::tuple<at::Tensor, at::Tensor>
  gru(const at::Tensor &data, const at::Tensor &batch_sizes,
      const at::Tensor &hx, at::TensorList params, bool has_biases,
      int64_t num_layers, double dropout, bool train, bool bidirectional);
  static std::tuple<at::Tensor, at::Tensor>
  rnn_tanh(const at::Tensor &input, const at::Tensor &hx, at::TensorList params,
           bool has_biases, int64_t num_layers, double dropout, bool train,
           bool bidirectional, bool batch_first);
  static std::tuple<at::Tensor, at::Tensor>
  rnn_tanh(const at::Tensor &data, const at::Tensor &batch_sizes,
           const at::Tensor &hx, at::TensorList params, bool has_biases,
           int64_t num_layers, double dropout, bool train, bool bidirectional);
  static std::tuple<at::Tensor, at::Tensor>
  rnn_relu(const at::Tensor &input, const at::Tensor &hx, at::TensorList params,
           bool has_biases, int64_t num_layers, double dropout, bool train,
           bool bidirectional, bool batch_first);
  static std::tuple<at::Tensor, at::Tensor>
  rnn_relu(const at::Tensor &data, const at::Tensor &batch_sizes,
           const at::Tensor &hx, at::TensorList params, bool has_biases,
           int64_t num_layers, double dropout, bool train, bool bidirectional);
  static std::tuple<at::Tensor, at::Tensor>
  lstm_cell(const at::Tensor &input, at::TensorList hx, const at::Tensor &w_ih,
            const at::Tensor &w_hh, const at::Tensor &b_ih,
            const at::Tensor &b_hh);
  static at::Tensor gru_cell(const at::Tensor &input, const at::Tensor &hx,
                             const at::Tensor &w_ih, const at::Tensor &w_hh,
                             const at::Tensor &b_ih, const at::Tensor &b_hh);
  static at::Tensor rnn_tanh_cell(const at::Tensor &input, const at::Tensor &hx,
                                  const at::Tensor &w_ih,
                                  const at::Tensor &w_hh,
                                  const at::Tensor &b_ih,
                                  const at::Tensor &b_hh);
  static at::Tensor rnn_relu_cell(const at::Tensor &input, const at::Tensor &hx,
                                  const at::Tensor &w_ih,
                                  const at::Tensor &w_hh,
                                  const at::Tensor &b_ih,
                                  const at::Tensor &b_hh);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  quantized_lstm(const at::Tensor &input, at::TensorList hx,
                 at::TensorList params, bool has_biases, int64_t num_layers,
                 double dropout, bool train, bool bidirectional,
                 bool batch_first, c10::optional<at::ScalarType> dtype,
                 bool use_dynamic);
  static std::tuple<at::Tensor, at::Tensor>
  quantized_gru(const at::Tensor &input, const at::Tensor &hx,
                at::TensorList params, bool has_biases, int64_t num_layers,
                double dropout, bool train, bool bidirectional,
                bool batch_first);
  static std::tuple<at::Tensor, at::Tensor>
  quantized_gru(const at::Tensor &data, const at::Tensor &batch_sizes,
                const at::Tensor &hx, at::TensorList params, bool has_biases,
                int64_t num_layers, double dropout, bool train,
                bool bidirectional);
  static std::tuple<at::Tensor, at::Tensor> quantized_lstm_cell(
      const at::Tensor &input, at::TensorList hx, const at::Tensor &w_ih,
      const at::Tensor &w_hh, const at::Tensor &b_ih, const at::Tensor &b_hh,
      const at::Tensor &packed_ih, const at::Tensor &packed_hh,
      const at::Tensor &col_offsets_ih, const at::Tensor &col_offsets_hh,
      at::Scalar scale_ih, at::Scalar scale_hh, at::Scalar zero_point_ih,
      at::Scalar zero_point_hh);
  static at::Tensor quantized_gru_cell(
      const at::Tensor &input, const at::Tensor &hx, const at::Tensor &w_ih,
      const at::Tensor &w_hh, const at::Tensor &b_ih, const at::Tensor &b_hh,
      const at::Tensor &packed_ih, const at::Tensor &packed_hh,
      const at::Tensor &col_offsets_ih, const at::Tensor &col_offsets_hh,
      at::Scalar scale_ih, at::Scalar scale_hh, at::Scalar zero_point_ih,
      at::Scalar zero_point_hh);
  static at::Tensor quantized_rnn_relu_cell(
      const at::Tensor &input, const at::Tensor &hx, const at::Tensor &w_ih,
      const at::Tensor &w_hh, const at::Tensor &b_ih, const at::Tensor &b_hh,
      const at::Tensor &packed_ih, const at::Tensor &packed_hh,
      const at::Tensor &col_offsets_ih, const at::Tensor &col_offsets_hh,
      at::Scalar scale_ih, at::Scalar scale_hh, at::Scalar zero_point_ih,
      at::Scalar zero_point_hh);
  static at::Tensor quantized_rnn_tanh_cell(
      const at::Tensor &input, const at::Tensor &hx, const at::Tensor &w_ih,
      const at::Tensor &w_hh, const at::Tensor &b_ih, const at::Tensor &b_hh,
      const at::Tensor &packed_ih, const at::Tensor &packed_hh,
      const at::Tensor &col_offsets_ih, const at::Tensor &col_offsets_hh,
      at::Scalar scale_ih, at::Scalar scale_hh, at::Scalar zero_point_ih,
      at::Scalar zero_point_hh);
  static std::tuple<at::Tensor, at::Tensor>
  _pack_padded_sequence(const at::Tensor &input, const at::Tensor &lengths,
                        bool batch_first);
  static at::Tensor _pack_padded_sequence_backward(
      const at::Tensor &grad, at::IntArrayRef input_size,
      const at::Tensor &batch_sizes, bool batch_first);
  static std::tuple<at::Tensor, at::Tensor>
  _pad_packed_sequence(const at::Tensor &data, const at::Tensor &batch_sizes,
                       bool batch_first, at::Scalar padding_value,
                       int64_t total_length);
  static at::Tensor &set_(at::Tensor &self, at::Storage source);
  static at::Tensor &set_(at::Tensor &self, at::Storage source,
                          int64_t storage_offset, at::IntArrayRef size,
                          at::IntArrayRef stride);
  static at::Tensor &set_(at::Tensor &self, const at::Tensor &source);
  static at::Tensor &set_(at::Tensor &self);
  static at::Tensor &set_quantizer_(at::Tensor &self,
                                    at::ConstQuantizerPtr quantizer);
  static bool is_set_to(const at::Tensor &self, const at::Tensor &tensor);
  static at::Tensor &masked_fill_(at::Tensor &self, const at::Tensor &mask,
                                  at::Scalar value);
  static at::Tensor masked_fill(const at::Tensor &self, const at::Tensor &mask,
                                at::Scalar value);
  static at::Tensor &masked_fill_(at::Tensor &self, const at::Tensor &mask,
                                  const at::Tensor &value);
  static at::Tensor masked_fill(const at::Tensor &self, const at::Tensor &mask,
                                const at::Tensor &value);
  static at::Tensor &masked_scatter_(at::Tensor &self, const at::Tensor &mask,
                                     const at::Tensor &source);
  static at::Tensor masked_scatter(const at::Tensor &self,
                                   const at::Tensor &mask,
                                   const at::Tensor &source);
  static at::Tensor view(const at::Tensor &self, at::IntArrayRef size);
  static at::Tensor &put_(at::Tensor &self, const at::Tensor &index,
                          const at::Tensor &source, bool accumulate);
  static at::Tensor &index_add_(at::Tensor &self, int64_t dim,
                                const at::Tensor &index,
                                const at::Tensor &source);
  static at::Tensor index_add(const at::Tensor &self, int64_t dim,
                              const at::Tensor &index,
                              const at::Tensor &source);
  static at::Tensor &index_fill_(at::Tensor &self, int64_t dim,
                                 const at::Tensor &index, at::Scalar value);
  static at::Tensor index_fill(const at::Tensor &self, int64_t dim,
                               const at::Tensor &index, at::Scalar value);
  static at::Tensor &index_fill_(at::Tensor &self, int64_t dim,
                                 const at::Tensor &index,
                                 const at::Tensor &value);
  static at::Tensor index_fill(const at::Tensor &self, int64_t dim,
                               const at::Tensor &index,
                               const at::Tensor &value);
  static at::Tensor &scatter_(at::Tensor &self, int64_t dim,
                              const at::Tensor &index, const at::Tensor &src);
  static at::Tensor scatter(const at::Tensor &self, int64_t dim,
                            const at::Tensor &index, const at::Tensor &src);
  static at::Tensor &scatter_(at::Tensor &self, int64_t dim,
                              const at::Tensor &index, at::Scalar value);
  static at::Tensor scatter(const at::Tensor &self, int64_t dim,
                            const at::Tensor &index, at::Scalar value);
  static at::Tensor &scatter_add_(at::Tensor &self, int64_t dim,
                                  const at::Tensor &index,
                                  const at::Tensor &src);
  static at::Tensor scatter_add(const at::Tensor &self, int64_t dim,
                                const at::Tensor &index, const at::Tensor &src);
  static at::Tensor &lt_(at::Tensor &self, at::Scalar other);
  static at::Tensor &lt_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &gt_(at::Tensor &self, at::Scalar other);
  static at::Tensor &gt_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &le_(at::Tensor &self, at::Scalar other);
  static at::Tensor &le_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &ge_(at::Tensor &self, at::Scalar other);
  static at::Tensor &ge_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &eq_(at::Tensor &self, at::Scalar other);
  static at::Tensor &eq_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &ne_(at::Tensor &self, at::Scalar other);
  static at::Tensor &ne_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor __and__(const at::Tensor &self, at::Scalar other);
  static at::Tensor __and__(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &__iand__(at::Tensor &self, at::Scalar other);
  static at::Tensor &__iand__(at::Tensor &self, const at::Tensor &other);
  static at::Tensor __or__(const at::Tensor &self, at::Scalar other);
  static at::Tensor __or__(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &__ior__(at::Tensor &self, at::Scalar other);
  static at::Tensor &__ior__(at::Tensor &self, const at::Tensor &other);
  static at::Tensor __xor__(const at::Tensor &self, at::Scalar other);
  static at::Tensor __xor__(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &__ixor__(at::Tensor &self, at::Scalar other);
  static at::Tensor &__ixor__(at::Tensor &self, const at::Tensor &other);
  static at::Tensor __lshift__(const at::Tensor &self, at::Scalar other);
  static at::Tensor __lshift__(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &__ilshift__(at::Tensor &self, at::Scalar other);
  static at::Tensor &__ilshift__(at::Tensor &self, const at::Tensor &other);
  static at::Tensor __rshift__(const at::Tensor &self, at::Scalar other);
  static at::Tensor __rshift__(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &__irshift__(at::Tensor &self, at::Scalar other);
  static at::Tensor &__irshift__(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &lgamma_(at::Tensor &self);
  static at::Tensor &atan2_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &tril_(at::Tensor &self, int64_t diagonal);
  static at::Tensor &triu_(at::Tensor &self, int64_t diagonal);
  static at::Tensor &digamma_(at::Tensor &self);
  static at::Tensor &polygamma_(at::Tensor &self, int64_t n);
  static at::Tensor &renorm_(at::Tensor &self, at::Scalar p, int64_t dim,
                             at::Scalar maxnorm);
  static at::Tensor &pow_(at::Tensor &self, at::Scalar exponent);
  static at::Tensor &pow_(at::Tensor &self, const at::Tensor &exponent);
  static at::Tensor &lerp_(at::Tensor &self, const at::Tensor &end,
                           at::Scalar weight);
  static at::Tensor &lerp_(at::Tensor &self, const at::Tensor &end,
                           const at::Tensor &weight);
  static at::Tensor &fmod_(at::Tensor &self, at::Scalar other);
  static at::Tensor &fmod_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &remainder_(at::Tensor &self, at::Scalar other);
  static at::Tensor &remainder_(at::Tensor &self, const at::Tensor &other);
  static at::Tensor &addbmm_(at::Tensor &self, const at::Tensor &batch1,
                             const at::Tensor &batch2, at::Scalar beta,
                             at::Scalar alpha);
  static at::Tensor &addbmm_out(at::Tensor &out, const at::Tensor &self,
                                const at::Tensor &batch1,
                                const at::Tensor &batch2, at::Scalar beta,
                                at::Scalar alpha);
  static at::Tensor addbmm(const at::Tensor &self, const at::Tensor &batch1,
                           const at::Tensor &batch2, at::Scalar beta,
                           at::Scalar alpha);
  static at::Tensor &addcdiv_(at::Tensor &self, const at::Tensor &tensor1,
                              const at::Tensor &tensor2, at::Scalar value);
  static at::Tensor &random_(at::Tensor &self, int64_t from, int64_t to,
                             at::Generator *generator);
  static at::Tensor &random_(at::Tensor &self, int64_t to,
                             at::Generator *generator);
  static at::Tensor &random_(at::Tensor &self, at::Generator *generator);
  static at::Tensor &uniform_(at::Tensor &self, double from, double to,
                              at::Generator *generator);
  static at::Tensor &normal_(at::Tensor &self, double mean, double std,
                             at::Generator *generator);
  static at::Tensor &cauchy_(at::Tensor &self, double median, double sigma,
                             at::Generator *generator);
  static at::Tensor &log_normal_(at::Tensor &self, double mean, double std,
                                 at::Generator *generator);
  static at::Tensor &exponential_(at::Tensor &self, double lambd,
                                  at::Generator *generator);
  static at::Tensor &geometric_(at::Tensor &self, double p,
                                at::Generator *generator);
  static at::Tensor &diag_out(at::Tensor &out, const at::Tensor &self,
                              int64_t diagonal);
  static at::Tensor diag(const at::Tensor &self, int64_t diagonal);
  static at::Tensor &cross_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &other,
                               c10::optional<int64_t> dim);
  static at::Tensor cross(const at::Tensor &self, const at::Tensor &other,
                          c10::optional<int64_t> dim);
  static at::Tensor &triu_out(at::Tensor &out, const at::Tensor &self,
                              int64_t diagonal);
  static at::Tensor triu(const at::Tensor &self, int64_t diagonal);
  static at::Tensor &tril_out(at::Tensor &out, const at::Tensor &self,
                              int64_t diagonal);
  static at::Tensor tril(const at::Tensor &self, int64_t diagonal);
  static at::Tensor tril_indices(int64_t row, int64_t col, int64_t offset,
                                 const at::TensorOptions &options);
  static at::Tensor triu_indices(int64_t row, int64_t col, int64_t offset,
                                 const at::TensorOptions &options);
  static at::Tensor trace(const at::Tensor &self);
  static at::Tensor &ne_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor ne(const at::Tensor &self, at::Scalar other);
  static at::Tensor &ne_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor ne(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &eq_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor eq(const at::Tensor &self, at::Scalar other);
  static at::Tensor &eq_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor eq(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &ge_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor ge(const at::Tensor &self, at::Scalar other);
  static at::Tensor &ge_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor ge(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &le_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor le(const at::Tensor &self, at::Scalar other);
  static at::Tensor &le_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor le(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &gt_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor gt(const at::Tensor &self, at::Scalar other);
  static at::Tensor &gt_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor gt(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &lt_out(at::Tensor &out, const at::Tensor &self,
                            at::Scalar other);
  static at::Tensor lt(const at::Tensor &self, at::Scalar other);
  static at::Tensor &lt_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &other);
  static at::Tensor lt(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &take_out(at::Tensor &out, const at::Tensor &self,
                              const at::Tensor &index);
  static at::Tensor take(const at::Tensor &self, const at::Tensor &index);
  static at::Tensor &index_select_out(at::Tensor &out, const at::Tensor &self,
                                      int64_t dim, const at::Tensor &index);
  static at::Tensor index_select(const at::Tensor &self, int64_t dim,
                                 const at::Tensor &index);
  static at::Tensor &masked_select_out(at::Tensor &out, const at::Tensor &self,
                                       const at::Tensor &mask);
  static at::Tensor masked_select(const at::Tensor &self,
                                  const at::Tensor &mask);
  static at::Tensor &nonzero_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor nonzero(const at::Tensor &self);
  static std::vector<at::Tensor> nonzero_numpy(const at::Tensor &self);
  static at::Tensor &gather_out(at::Tensor &out, const at::Tensor &self,
                                int64_t dim, const at::Tensor &index,
                                bool sparse_grad);
  static at::Tensor gather(const at::Tensor &self, int64_t dim,
                           const at::Tensor &index, bool sparse_grad);
  static at::Tensor _gather_sparse_backward(const at::Tensor &self, int64_t dim,
                                            const at::Tensor &index,
                                            const at::Tensor &grad);
  static at::Tensor &addcmul_out(at::Tensor &out, const at::Tensor &self,
                                 const at::Tensor &tensor1,
                                 const at::Tensor &tensor2, at::Scalar value);
  static at::Tensor addcmul(const at::Tensor &self, const at::Tensor &tensor1,
                            const at::Tensor &tensor2, at::Scalar value);
  static at::Tensor &addcmul_(at::Tensor &self, const at::Tensor &tensor1,
                              const at::Tensor &tensor2, at::Scalar value);
  static at::Tensor &addcdiv_out(at::Tensor &out, const at::Tensor &self,
                                 const at::Tensor &tensor1,
                                 const at::Tensor &tensor2, at::Scalar value);
  static at::Tensor addcdiv(const at::Tensor &self, const at::Tensor &tensor1,
                            const at::Tensor &tensor2, at::Scalar value);
  static std::tuple<at::Tensor &, at::Tensor &>
  lstsq_out(at::Tensor &X, at::Tensor &qr, const at::Tensor &self,
            const at::Tensor &A);
  static std::tuple<at::Tensor, at::Tensor> lstsq(const at::Tensor &self,
                                                  const at::Tensor &A);
  static std::tuple<at::Tensor &, at::Tensor &>
  triangular_solve_out(at::Tensor &X, at::Tensor &M, const at::Tensor &self,
                       const at::Tensor &A, bool upper, bool transpose,
                       bool unitriangular);
  static std::tuple<at::Tensor, at::Tensor>
  triangular_solve(const at::Tensor &self, const at::Tensor &A, bool upper,
                   bool transpose, bool unitriangular);
  static std::tuple<at::Tensor, at::Tensor>
  _triangular_solve_helper(const at::Tensor &self, const at::Tensor &A,
                           bool upper, bool transpose, bool unitriangular);
  static std::tuple<at::Tensor &, at::Tensor &>
  symeig_out(at::Tensor &e, at::Tensor &V, const at::Tensor &self,
             bool eigenvectors, bool upper);
  static std::tuple<at::Tensor, at::Tensor>
  symeig(const at::Tensor &self, bool eigenvectors, bool upper);
  static std::tuple<at::Tensor, at::Tensor>
  _symeig_helper(const at::Tensor &self, bool eigenvectors, bool upper);
  static std::tuple<at::Tensor &, at::Tensor &> eig_out(at::Tensor &e,
                                                        at::Tensor &v,
                                                        const at::Tensor &self,
                                                        bool eigenvectors);
  static std::tuple<at::Tensor, at::Tensor> eig(const at::Tensor &self,
                                                bool eigenvectors);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  svd_out(at::Tensor &U, at::Tensor &S, at::Tensor &V, const at::Tensor &self,
          bool some, bool compute_uv);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  svd(const at::Tensor &self, bool some, bool compute_uv);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _svd_helper(const at::Tensor &self, bool some, bool compute_uv);
  static at::Tensor &cholesky_out(at::Tensor &out, const at::Tensor &self,
                                  bool upper);
  static at::Tensor cholesky(const at::Tensor &self, bool upper);
  static at::Tensor _cholesky_helper(const at::Tensor &self, bool upper);
  static at::Tensor &cholesky_solve_out(at::Tensor &out, const at::Tensor &self,
                                        const at::Tensor &input2, bool upper);
  static at::Tensor cholesky_solve(const at::Tensor &self,
                                   const at::Tensor &input2, bool upper);
  static at::Tensor _cholesky_solve_helper(const at::Tensor &self,
                                           const at::Tensor &A, bool upper);
  static std::tuple<at::Tensor, at::Tensor> solve(const at::Tensor &self,
                                                  const at::Tensor &A);
  static std::tuple<at::Tensor &, at::Tensor &>
  solve_out(at::Tensor &solution, at::Tensor &lu, const at::Tensor &self,
            const at::Tensor &A);
  static std::tuple<at::Tensor, at::Tensor>
  _solve_helper(const at::Tensor &self, const at::Tensor &A);
  static at::Tensor &cholesky_inverse_out(at::Tensor &out,
                                          const at::Tensor &self, bool upper);
  static at::Tensor cholesky_inverse(const at::Tensor &self, bool upper);
  static std::tuple<at::Tensor &, at::Tensor &>
  qr_out(at::Tensor &Q, at::Tensor &R, const at::Tensor &self, bool some);
  static std::tuple<at::Tensor, at::Tensor> qr(const at::Tensor &self,
                                               bool some);
  static std::tuple<at::Tensor, at::Tensor> _qr_helper(const at::Tensor &self,
                                                       bool some);
  static std::tuple<at::Tensor &, at::Tensor &>
  geqrf_out(at::Tensor &a, at::Tensor &tau, const at::Tensor &self);
  static std::tuple<at::Tensor, at::Tensor> geqrf(const at::Tensor &self);
  static at::Tensor &orgqr_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &input2);
  static at::Tensor orgqr(const at::Tensor &self, const at::Tensor &input2);
  static at::Tensor &ormqr_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &input2,
                               const at::Tensor &input3, bool left,
                               bool transpose);
  static at::Tensor ormqr(const at::Tensor &self, const at::Tensor &input2,
                          const at::Tensor &input3, bool left, bool transpose);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  _lu_with_info(const at::Tensor &self, bool pivot, bool check_errors);
  static at::Tensor &lu_solve_out(at::Tensor &out, const at::Tensor &self,
                                  const at::Tensor &LU_data,
                                  const at::Tensor &LU_pivots);
  static at::Tensor lu_solve(const at::Tensor &self, const at::Tensor &LU_data,
                             const at::Tensor &LU_pivots);
  static at::Tensor _lu_solve_helper(const at::Tensor &self,
                                     const at::Tensor &LU_data,
                                     const at::Tensor &LU_pivots);
  static at::Tensor &multinomial_out(at::Tensor &out, const at::Tensor &self,
                                     int64_t num_samples, bool replacement,
                                     at::Generator *generator);
  static at::Tensor multinomial(const at::Tensor &self, int64_t num_samples,
                                bool replacement, at::Generator *generator);
  static std::tuple<at::Tensor, at::Tensor>
  _multinomial_alias_setup(const at::Tensor &probs);
  static at::Tensor _multinomial_alias_draw(const at::Tensor &J,
                                            const at::Tensor &q,
                                            int64_t num_samples,
                                            at::Generator *generator);
  static at::Tensor &lgamma_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor lgamma(const at::Tensor &self);
  static at::Tensor &digamma_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor digamma(const at::Tensor &self);
  static at::Tensor &polygamma_out(at::Tensor &out, int64_t n,
                                   const at::Tensor &self);
  static at::Tensor polygamma(int64_t n, const at::Tensor &self);
  static at::Tensor erfinv(const at::Tensor &self);
  static at::Tensor &erfinv_(at::Tensor &self);
  static at::Tensor &erfinv_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor sign(const at::Tensor &self);
  static at::Tensor &sign_(at::Tensor &self);
  static at::Tensor &sign_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor dist(const at::Tensor &self, const at::Tensor &other,
                         at::Scalar p);
  static at::Tensor &atan2_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &other);
  static at::Tensor atan2(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &lerp_out(at::Tensor &out, const at::Tensor &self,
                              const at::Tensor &end, at::Scalar weight);
  static at::Tensor &lerp_out(at::Tensor &out, const at::Tensor &self,
                              const at::Tensor &end, const at::Tensor &weight);
  static at::Tensor lerp(const at::Tensor &self, const at::Tensor &end,
                         at::Scalar weight);
  static at::Tensor lerp(const at::Tensor &self, const at::Tensor &end,
                         const at::Tensor &weight);
  static at::Tensor &histc_out(at::Tensor &out, const at::Tensor &self,
                               int64_t bins, at::Scalar min, at::Scalar max);
  static at::Tensor histc(const at::Tensor &self, int64_t bins, at::Scalar min,
                          at::Scalar max);
  static at::Tensor &fmod_out(at::Tensor &out, const at::Tensor &self,
                              at::Scalar other);
  static at::Tensor fmod(const at::Tensor &self, at::Scalar other);
  static at::Tensor &fmod_out(at::Tensor &out, const at::Tensor &self,
                              const at::Tensor &other);
  static at::Tensor fmod(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &remainder_out(at::Tensor &out, const at::Tensor &self,
                                   at::Scalar other);
  static at::Tensor remainder(const at::Tensor &self, at::Scalar other);
  static at::Tensor &remainder_out(at::Tensor &out, const at::Tensor &self,
                                   const at::Tensor &other);
  static at::Tensor remainder(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &min_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other);
  static at::Tensor min(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor min(const at::Tensor &self);
  static at::Tensor &max_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &other);
  static at::Tensor max(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor max(const at::Tensor &self);
  static at::Tensor median(const at::Tensor &self);
  static std::tuple<at::Tensor &, at::Tensor &>
  sort_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
           int64_t dim, bool descending);
  static std::tuple<at::Tensor, at::Tensor> sort(const at::Tensor &self,
                                                 int64_t dim, bool descending);
  static at::Tensor argsort(const at::Tensor &self, int64_t dim,
                            bool descending);
  static std::tuple<at::Tensor &, at::Tensor &>
  topk_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
           int64_t k, int64_t dim, bool largest, bool sorted);
  static std::tuple<at::Tensor, at::Tensor> topk(const at::Tensor &self,
                                                 int64_t k, int64_t dim,
                                                 bool largest, bool sorted);
  static at::Tensor all(const at::Tensor &self);
  static at::Tensor any(const at::Tensor &self);
  static at::Tensor &renorm_out(at::Tensor &out, const at::Tensor &self,
                                at::Scalar p, int64_t dim, at::Scalar maxnorm);
  static at::Tensor renorm(const at::Tensor &self, at::Scalar p, int64_t dim,
                           at::Scalar maxnorm);
  static at::Tensor unfold(const at::Tensor &self, int64_t dimension,
                           int64_t size, int64_t step);
  static bool equal(const at::Tensor &self, const at::Tensor &other);
  static at::Tensor &pow_out(at::Tensor &out, const at::Tensor &self,
                             const at::Tensor &exponent);
  static at::Tensor pow(const at::Tensor &self, const at::Tensor &exponent);
  static at::Tensor &pow_out(at::Tensor &out, at::Scalar self,
                             const at::Tensor &exponent);
  static at::Tensor pow(at::Scalar self, const at::Tensor &exponent);
  static at::Tensor &normal_out(at::Tensor &out, const at::Tensor &mean,
                                double std, at::Generator *generator);
  static at::Tensor normal(const at::Tensor &mean, double std,
                           at::Generator *generator);
  static at::Tensor &normal_out(at::Tensor &out, double mean,
                                const at::Tensor &std,
                                at::Generator *generator);
  static at::Tensor normal(double mean, const at::Tensor &std,
                           at::Generator *generator);
  static at::Tensor &normal_out(at::Tensor &out, const at::Tensor &mean,
                                const at::Tensor &std,
                                at::Generator *generator);
  static at::Tensor normal(const at::Tensor &mean, const at::Tensor &std,
                           at::Generator *generator);
  static at::Tensor normal(double mean, double std, at::IntArrayRef size,
                           at::Generator *generator,
                           const at::TensorOptions &options);
  static at::Tensor &normal_out(at::Tensor &out, double mean, double std,
                                at::IntArrayRef size, at::Generator *generator);
  static at::Tensor alias(const at::Tensor &self);
  static at::Tensor _addr(const at::Tensor &self, const at::Tensor &vec1,
                          const at::Tensor &vec2, at::Scalar beta,
                          at::Scalar alpha);
  static at::Tensor &_addr_(at::Tensor &self, const at::Tensor &vec1,
                            const at::Tensor &vec2, at::Scalar beta,
                            at::Scalar alpha);
  static at::Tensor &_addr_out(at::Tensor &out, const at::Tensor &self,
                               const at::Tensor &vec1, const at::Tensor &vec2,
                               at::Scalar beta, at::Scalar alpha);
  static at::Tensor &_index_copy_(at::Tensor &self, int64_t dim,
                                  const at::Tensor &index,
                                  const at::Tensor &source);
  static at::Tensor _cumsum(const at::Tensor &self, int64_t dim);
  static at::Tensor &_cumsum_out(at::Tensor &out, const at::Tensor &self,
                                 int64_t dim);
  static at::Tensor _cumprod(const at::Tensor &self, int64_t dim);
  static at::Tensor &_cumprod_out(at::Tensor &out, const at::Tensor &self,
                                  int64_t dim);
  static at::Tensor _var(const at::Tensor &self, bool unbiased);
  static at::Tensor _std(const at::Tensor &self, bool unbiased);
  static at::Tensor &_addmm_out(at::Tensor &out, const at::Tensor &self,
                                const at::Tensor &mat1, const at::Tensor &mat2,
                                at::Scalar beta, at::Scalar alpha);
  static at::Tensor _addmm(const at::Tensor &self, const at::Tensor &mat1,
                           const at::Tensor &mat2, at::Scalar beta,
                           at::Scalar alpha);
  static at::Tensor &_addmm_(at::Tensor &self, const at::Tensor &mat1,
                             const at::Tensor &mat2, at::Scalar beta,
                             at::Scalar alpha);
  static at::Tensor _cat(at::TensorList tensors, int64_t dim);
  static at::Tensor &_cat_out(at::Tensor &out, at::TensorList tensors,
                              int64_t dim);
  static std::tuple<at::Tensor, at::Tensor> _mode(const at::Tensor &self,
                                                  int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  _mode_out(at::Tensor &values, at::Tensor &indices, const at::Tensor &self,
            int64_t dim, bool keepdim);
  static std::tuple<at::Tensor, at::Tensor> _max(const at::Tensor &self,
                                                 int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  _max_out(at::Tensor &max, at::Tensor &max_indices, const at::Tensor &self,
           int64_t dim, bool keepdim);
  static std::tuple<at::Tensor, at::Tensor> _min(const at::Tensor &self,
                                                 int64_t dim, bool keepdim);
  static std::tuple<at::Tensor &, at::Tensor &>
  _min_out(at::Tensor &min, at::Tensor &min_indices, const at::Tensor &self,
           int64_t dim, bool keepdim);
  static at::Tensor &binary_cross_entropy_out(at::Tensor &out,
                                              const at::Tensor &self,
                                              const at::Tensor &target,
                                              const at::Tensor &weight,
                                              int64_t reduction);
  static at::Tensor binary_cross_entropy(const at::Tensor &self,
                                         const at::Tensor &target,
                                         const at::Tensor &weight,
                                         int64_t reduction);
  static at::Tensor &binary_cross_entropy_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &target,
      const at::Tensor &weight, int64_t reduction);
  static at::Tensor binary_cross_entropy_backward(const at::Tensor &grad_output,
                                                  const at::Tensor &self,
                                                  const at::Tensor &target,
                                                  const at::Tensor &weight,
                                                  int64_t reduction);
  static at::Tensor &mse_loss_out(at::Tensor &out, const at::Tensor &self,
                                  const at::Tensor &target, int64_t reduction);
  static at::Tensor mse_loss(const at::Tensor &self, const at::Tensor &target,
                             int64_t reduction);
  static at::Tensor &mse_loss_backward_out(at::Tensor &grad_input,
                                           const at::Tensor &grad_output,
                                           const at::Tensor &self,
                                           const at::Tensor &target,
                                           int64_t reduction);
  static at::Tensor mse_loss_backward(const at::Tensor &grad_output,
                                      const at::Tensor &self,
                                      const at::Tensor &target,
                                      int64_t reduction);
  static at::Tensor &l1_loss_out(at::Tensor &out, const at::Tensor &self,
                                 const at::Tensor &target, int64_t reduction);
  static at::Tensor l1_loss(const at::Tensor &self, const at::Tensor &target,
                            int64_t reduction);
  static at::Tensor &l1_loss_backward_out(at::Tensor &grad_input,
                                          const at::Tensor &grad_output,
                                          const at::Tensor &self,
                                          const at::Tensor &target,
                                          int64_t reduction);
  static at::Tensor l1_loss_backward(const at::Tensor &grad_output,
                                     const at::Tensor &self,
                                     const at::Tensor &target,
                                     int64_t reduction);
  static at::Tensor &multi_margin_loss_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           const at::Tensor &target,
                                           at::Scalar p, at::Scalar margin,
                                           const at::Tensor &weight,
                                           int64_t reduction);
  static at::Tensor multi_margin_loss(const at::Tensor &self,
                                      const at::Tensor &target, at::Scalar p,
                                      at::Scalar margin,
                                      const at::Tensor &weight,
                                      int64_t reduction);
  static at::Tensor &multi_margin_loss_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &target, at::Scalar p,
      at::Scalar margin, const at::Tensor &weight, int64_t reduction);
  static at::Tensor multi_margin_loss_backward(const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               const at::Tensor &target,
                                               at::Scalar p, at::Scalar margin,
                                               const at::Tensor &weight,
                                               int64_t reduction);
  static at::Tensor &multilabel_margin_loss_out(at::Tensor &out,
                                                const at::Tensor &self,
                                                const at::Tensor &target,
                                                int64_t reduction);
  static at::Tensor multilabel_margin_loss(const at::Tensor &self,
                                           const at::Tensor &target,
                                           int64_t reduction);
  static std::tuple<at::Tensor &, at::Tensor &>
  multilabel_margin_loss_forward_out(at::Tensor &output, at::Tensor &is_target,
                                     const at::Tensor &self,
                                     const at::Tensor &target,
                                     int64_t reduction);
  static std::tuple<at::Tensor, at::Tensor>
  multilabel_margin_loss_forward(const at::Tensor &self,
                                 const at::Tensor &target, int64_t reduction);
  static at::Tensor &multilabel_margin_loss_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &target, int64_t reduction,
      const at::Tensor &is_target);
  static at::Tensor multilabel_margin_loss_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &target, int64_t reduction, const at::Tensor &is_target);
  static at::Tensor &nll_loss_out(at::Tensor &out, const at::Tensor &self,
                                  const at::Tensor &target,
                                  const at::Tensor &weight, int64_t reduction,
                                  int64_t ignore_index);
  static at::Tensor nll_loss(const at::Tensor &self, const at::Tensor &target,
                             const at::Tensor &weight, int64_t reduction,
                             int64_t ignore_index);
  static std::tuple<at::Tensor &, at::Tensor &>
  nll_loss_forward_out(at::Tensor &output, at::Tensor &total_weight,
                       const at::Tensor &self, const at::Tensor &target,
                       const at::Tensor &weight, int64_t reduction,
                       int64_t ignore_index);
  static std::tuple<at::Tensor, at::Tensor>
  nll_loss_forward(const at::Tensor &self, const at::Tensor &target,
                   const at::Tensor &weight, int64_t reduction,
                   int64_t ignore_index);
  static at::Tensor &
  nll_loss_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                        const at::Tensor &self, const at::Tensor &target,
                        const at::Tensor &weight, int64_t reduction,
                        int64_t ignore_index, const at::Tensor &total_weight);
  static at::Tensor nll_loss_backward(const at::Tensor &grad_output,
                                      const at::Tensor &self,
                                      const at::Tensor &target,
                                      const at::Tensor &weight,
                                      int64_t reduction, int64_t ignore_index,
                                      const at::Tensor &total_weight);
  static at::Tensor &nll_loss2d_out(at::Tensor &out, const at::Tensor &self,
                                    const at::Tensor &target,
                                    const at::Tensor &weight, int64_t reduction,
                                    int64_t ignore_index);
  static at::Tensor nll_loss2d(const at::Tensor &self, const at::Tensor &target,
                               const at::Tensor &weight, int64_t reduction,
                               int64_t ignore_index);
  static std::tuple<at::Tensor &, at::Tensor &>
  nll_loss2d_forward_out(at::Tensor &output, at::Tensor &total_weight,
                         const at::Tensor &self, const at::Tensor &target,
                         const at::Tensor &weight, int64_t reduction,
                         int64_t ignore_index);
  static std::tuple<at::Tensor, at::Tensor>
  nll_loss2d_forward(const at::Tensor &self, const at::Tensor &target,
                     const at::Tensor &weight, int64_t reduction,
                     int64_t ignore_index);
  static at::Tensor &
  nll_loss2d_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                          const at::Tensor &self, const at::Tensor &target,
                          const at::Tensor &weight, int64_t reduction,
                          int64_t ignore_index, const at::Tensor &total_weight);
  static at::Tensor nll_loss2d_backward(const at::Tensor &grad_output,
                                        const at::Tensor &self,
                                        const at::Tensor &target,
                                        const at::Tensor &weight,
                                        int64_t reduction, int64_t ignore_index,
                                        const at::Tensor &total_weight);
  static at::Tensor &smooth_l1_loss_out(at::Tensor &out, const at::Tensor &self,
                                        const at::Tensor &target,
                                        int64_t reduction);
  static at::Tensor smooth_l1_loss(const at::Tensor &self,
                                   const at::Tensor &target, int64_t reduction);
  static at::Tensor &smooth_l1_loss_backward_out(at::Tensor &grad_input,
                                                 const at::Tensor &grad_output,
                                                 const at::Tensor &self,
                                                 const at::Tensor &target,
                                                 int64_t reduction);
  static at::Tensor smooth_l1_loss_backward(const at::Tensor &grad_output,
                                            const at::Tensor &self,
                                            const at::Tensor &target,
                                            int64_t reduction);
  static at::Tensor &soft_margin_loss_out(at::Tensor &out,
                                          const at::Tensor &self,
                                          const at::Tensor &target,
                                          int64_t reduction);
  static at::Tensor soft_margin_loss(const at::Tensor &self,
                                     const at::Tensor &target,
                                     int64_t reduction);
  static at::Tensor &soft_margin_loss_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &target, int64_t reduction);
  static at::Tensor soft_margin_loss_backward(const at::Tensor &grad_output,
                                              const at::Tensor &self,
                                              const at::Tensor &target,
                                              int64_t reduction);
  static at::Tensor &elu_out(at::Tensor &out, const at::Tensor &self,
                             at::Scalar alpha, at::Scalar scale,
                             at::Scalar input_scale);
  static at::Tensor elu(const at::Tensor &self, at::Scalar alpha,
                        at::Scalar scale, at::Scalar input_scale);
  static at::Tensor &elu_backward_out(at::Tensor &grad_input,
                                      const at::Tensor &grad_output,
                                      at::Scalar alpha, at::Scalar scale,
                                      at::Scalar input_scale,
                                      const at::Tensor &output);
  static at::Tensor elu_backward(const at::Tensor &grad_output,
                                 at::Scalar alpha, at::Scalar scale,
                                 at::Scalar input_scale,
                                 const at::Tensor &output);
  static at::Tensor &elu_(at::Tensor &self, at::Scalar alpha, at::Scalar scale,
                          at::Scalar input_scale);
  static at::Tensor &glu_out(at::Tensor &out, const at::Tensor &self,
                             int64_t dim);
  static at::Tensor glu(const at::Tensor &self, int64_t dim);
  static at::Tensor &glu_backward_out(at::Tensor &grad_input,
                                      const at::Tensor &grad_output,
                                      const at::Tensor &self, int64_t dim);
  static at::Tensor glu_backward(const at::Tensor &grad_output,
                                 const at::Tensor &self, int64_t dim);
  static at::Tensor &hardtanh_out(at::Tensor &out, const at::Tensor &self,
                                  at::Scalar min_val, at::Scalar max_val);
  static at::Tensor hardtanh(const at::Tensor &self, at::Scalar min_val,
                             at::Scalar max_val);
  static at::Tensor &hardtanh_backward_out(at::Tensor &grad_input,
                                           const at::Tensor &grad_output,
                                           const at::Tensor &self,
                                           at::Scalar min_val,
                                           at::Scalar max_val);
  static at::Tensor hardtanh_backward(const at::Tensor &grad_output,
                                      const at::Tensor &self,
                                      at::Scalar min_val, at::Scalar max_val);
  static at::Tensor &hardtanh_(at::Tensor &self, at::Scalar min_val,
                               at::Scalar max_val);
  static at::Tensor &leaky_relu_out(at::Tensor &out, const at::Tensor &self,
                                    at::Scalar negative_slope);
  static at::Tensor leaky_relu(const at::Tensor &self,
                               at::Scalar negative_slope);
  static at::Tensor &leaky_relu_backward_out(at::Tensor &grad_input,
                                             const at::Tensor &grad_output,
                                             const at::Tensor &self,
                                             at::Scalar negative_slope);
  static at::Tensor leaky_relu_backward(const at::Tensor &grad_output,
                                        const at::Tensor &self,
                                        at::Scalar negative_slope);
  static at::Tensor &leaky_relu_(at::Tensor &self, at::Scalar negative_slope);
  static at::Tensor &log_sigmoid_out(at::Tensor &out, const at::Tensor &self);
  static at::Tensor log_sigmoid(const at::Tensor &self);
  static std::tuple<at::Tensor &, at::Tensor &>
  log_sigmoid_forward_out(at::Tensor &output, at::Tensor &buffer,
                          const at::Tensor &self);
  static std::tuple<at::Tensor, at::Tensor>
  log_sigmoid_forward(const at::Tensor &self);
  static at::Tensor &log_sigmoid_backward_out(at::Tensor &grad_input,
                                              const at::Tensor &grad_output,
                                              const at::Tensor &self,
                                              const at::Tensor &buffer);
  static at::Tensor log_sigmoid_backward(const at::Tensor &grad_output,
                                         const at::Tensor &self,
                                         const at::Tensor &buffer);
  static at::Tensor &rrelu_with_noise_out(at::Tensor &out,
                                          const at::Tensor &self,
                                          const at::Tensor &noise,
                                          at::Scalar lower, at::Scalar upper,
                                          bool training,
                                          at::Generator *generator);
  static at::Tensor rrelu_with_noise(const at::Tensor &self,
                                     const at::Tensor &noise, at::Scalar lower,
                                     at::Scalar upper, bool training,
                                     at::Generator *generator);
  static at::Tensor &rrelu_with_noise_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &noise, at::Scalar lower,
      at::Scalar upper, bool training);
  static at::Tensor rrelu_with_noise_backward(const at::Tensor &grad_output,
                                              const at::Tensor &self,
                                              const at::Tensor &noise,
                                              at::Scalar lower,
                                              at::Scalar upper, bool training);
  static at::Tensor &rrelu_with_noise_(at::Tensor &self,
                                       const at::Tensor &noise,
                                       at::Scalar lower, at::Scalar upper,
                                       bool training, at::Generator *generator);
  static at::Tensor &softplus_out(at::Tensor &out, const at::Tensor &self,
                                  at::Scalar beta, at::Scalar threshold);
  static at::Tensor softplus(const at::Tensor &self, at::Scalar beta,
                             at::Scalar threshold);
  static at::Tensor &
  softplus_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                        const at::Tensor &self, at::Scalar beta,
                        at::Scalar threshold, const at::Tensor &output);
  static at::Tensor softplus_backward(const at::Tensor &grad_output,
                                      const at::Tensor &self, at::Scalar beta,
                                      at::Scalar threshold,
                                      const at::Tensor &output);
  static at::Tensor &softshrink_out(at::Tensor &out, const at::Tensor &self,
                                    at::Scalar lambd);
  static at::Tensor softshrink(const at::Tensor &self, at::Scalar lambd);
  static at::Tensor &softshrink_backward_out(at::Tensor &grad_input,
                                             const at::Tensor &grad_output,
                                             const at::Tensor &self,
                                             at::Scalar lambd);
  static at::Tensor softshrink_backward(const at::Tensor &grad_output,
                                        const at::Tensor &self,
                                        at::Scalar lambd);
  static at::Tensor &adaptive_avg_pool2d_out(at::Tensor &out,
                                             const at::Tensor &self,
                                             at::IntArrayRef output_size);
  static at::Tensor adaptive_avg_pool2d(const at::Tensor &self,
                                        at::IntArrayRef output_size);
  static at::Tensor mkldnn_adaptive_avg_pool2d(const at::Tensor &self,
                                               at::IntArrayRef output_size);
  static at::Tensor _adaptive_avg_pool2d(const at::Tensor &self,
                                         at::IntArrayRef output_size);
  static at::Tensor _adaptive_avg_pool2d_backward(const at::Tensor &grad_output,
                                                  const at::Tensor &self);
  static at::Tensor &adaptive_avg_pool3d_out(at::Tensor &out,
                                             const at::Tensor &self,
                                             at::IntArrayRef output_size);
  static at::Tensor adaptive_avg_pool3d(const at::Tensor &self,
                                        at::IntArrayRef output_size);
  static at::Tensor &
  adaptive_avg_pool3d_backward_out(at::Tensor &grad_input,
                                   const at::Tensor &grad_output,
                                   const at::Tensor &self);
  static at::Tensor adaptive_avg_pool3d_backward(const at::Tensor &grad_output,
                                                 const at::Tensor &self);
  static std::tuple<at::Tensor &, at::Tensor &>
  adaptive_max_pool2d_out(at::Tensor &out, at::Tensor &indices,
                          const at::Tensor &self, at::IntArrayRef output_size);
  static std::tuple<at::Tensor, at::Tensor>
  adaptive_max_pool2d(const at::Tensor &self, at::IntArrayRef output_size);
  static at::Tensor &adaptive_max_pool2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &indices);
  static at::Tensor adaptive_max_pool2d_backward(const at::Tensor &grad_output,
                                                 const at::Tensor &self,
                                                 const at::Tensor &indices);
  static std::tuple<at::Tensor &, at::Tensor &>
  adaptive_max_pool3d_out(at::Tensor &out, at::Tensor &indices,
                          const at::Tensor &self, at::IntArrayRef output_size);
  static std::tuple<at::Tensor, at::Tensor>
  adaptive_max_pool3d(const at::Tensor &self, at::IntArrayRef output_size);
  static at::Tensor &adaptive_max_pool3d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, const at::Tensor &indices);
  static at::Tensor adaptive_max_pool3d_backward(const at::Tensor &grad_output,
                                                 const at::Tensor &self,
                                                 const at::Tensor &indices);
  static at::Tensor &avg_pool2d_out(at::Tensor &out, const at::Tensor &self,
                                    at::IntArrayRef kernel_size,
                                    at::IntArrayRef stride,
                                    at::IntArrayRef padding, bool ceil_mode,
                                    bool count_include_pad,
                                    c10::optional<int64_t> divisor_override);
  static at::Tensor avg_pool2d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               bool ceil_mode, bool count_include_pad,
                               c10::optional<int64_t> divisor_override);
  static at::Tensor &
  avg_pool2d_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                          const at::Tensor &self, at::IntArrayRef kernel_size,
                          at::IntArrayRef stride, at::IntArrayRef padding,
                          bool ceil_mode, bool count_include_pad,
                          c10::optional<int64_t> divisor_override);
  static at::Tensor
  avg_pool2d_backward(const at::Tensor &grad_output, const at::Tensor &self,
                      at::IntArrayRef kernel_size, at::IntArrayRef stride,
                      at::IntArrayRef padding, bool ceil_mode,
                      bool count_include_pad,
                      c10::optional<int64_t> divisor_override);
  static at::Tensor &avg_pool3d_out(at::Tensor &out, const at::Tensor &self,
                                    at::IntArrayRef kernel_size,
                                    at::IntArrayRef stride,
                                    at::IntArrayRef padding, bool ceil_mode,
                                    bool count_include_pad,
                                    c10::optional<int64_t> divisor_override);
  static at::Tensor avg_pool3d(const at::Tensor &self,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               bool ceil_mode, bool count_include_pad,
                               c10::optional<int64_t> divisor_override);
  static at::Tensor &
  avg_pool3d_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                          const at::Tensor &self, at::IntArrayRef kernel_size,
                          at::IntArrayRef stride, at::IntArrayRef padding,
                          bool ceil_mode, bool count_include_pad,
                          c10::optional<int64_t> divisor_override);
  static at::Tensor
  avg_pool3d_backward(const at::Tensor &grad_output, const at::Tensor &self,
                      at::IntArrayRef kernel_size, at::IntArrayRef stride,
                      at::IntArrayRef padding, bool ceil_mode,
                      bool count_include_pad,
                      c10::optional<int64_t> divisor_override);
  static std::tuple<at::Tensor &, at::Tensor &>
  fractional_max_pool2d_out(at::Tensor &output, at::Tensor &indices,
                            const at::Tensor &self, at::IntArrayRef kernel_size,
                            at::IntArrayRef output_size,
                            const at::Tensor &random_samples);
  static std::tuple<at::Tensor, at::Tensor>
  fractional_max_pool2d(const at::Tensor &self, at::IntArrayRef kernel_size,
                        at::IntArrayRef output_size,
                        const at::Tensor &random_samples);
  static at::Tensor &fractional_max_pool2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef kernel_size,
      at::IntArrayRef output_size, const at::Tensor &indices);
  static at::Tensor fractional_max_pool2d_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef output_size,
      const at::Tensor &indices);
  static std::tuple<at::Tensor &, at::Tensor &>
  fractional_max_pool3d_out(at::Tensor &output, at::Tensor &indices,
                            const at::Tensor &self, at::IntArrayRef kernel_size,
                            at::IntArrayRef output_size,
                            const at::Tensor &random_samples);
  static std::tuple<at::Tensor, at::Tensor>
  fractional_max_pool3d(const at::Tensor &self, at::IntArrayRef kernel_size,
                        at::IntArrayRef output_size,
                        const at::Tensor &random_samples);
  static at::Tensor &fractional_max_pool3d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef kernel_size,
      at::IntArrayRef output_size, const at::Tensor &indices);
  static at::Tensor fractional_max_pool3d_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef output_size,
      const at::Tensor &indices);
  static std::tuple<at::Tensor &, at::Tensor &> max_pool2d_with_indices_out(
      at::Tensor &out, at::Tensor &indices, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef stride,
      at::IntArrayRef padding, at::IntArrayRef dilation, bool ceil_mode);
  static std::tuple<at::Tensor, at::Tensor>
  max_pool2d_with_indices(const at::Tensor &self, at::IntArrayRef kernel_size,
                          at::IntArrayRef stride, at::IntArrayRef padding,
                          at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor &max_pool2d_with_indices_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation,
      bool ceil_mode, const at::Tensor &indices);
  static at::Tensor max_pool2d_with_indices_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef stride,
      at::IntArrayRef padding, at::IntArrayRef dilation, bool ceil_mode,
      const at::Tensor &indices);
  static std::tuple<at::Tensor &, at::Tensor &> max_pool3d_with_indices_out(
      at::Tensor &out, at::Tensor &indices, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef stride,
      at::IntArrayRef padding, at::IntArrayRef dilation, bool ceil_mode);
  static std::tuple<at::Tensor, at::Tensor>
  max_pool3d_with_indices(const at::Tensor &self, at::IntArrayRef kernel_size,
                          at::IntArrayRef stride, at::IntArrayRef padding,
                          at::IntArrayRef dilation, bool ceil_mode);
  static at::Tensor &max_pool3d_with_indices_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation,
      bool ceil_mode, const at::Tensor &indices);
  static at::Tensor max_pool3d_with_indices_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      at::IntArrayRef kernel_size, at::IntArrayRef stride,
      at::IntArrayRef padding, at::IntArrayRef dilation, bool ceil_mode,
      const at::Tensor &indices);
  static at::Tensor &max_unpool2d_out(at::Tensor &out, const at::Tensor &self,
                                      const at::Tensor &indices,
                                      at::IntArrayRef output_size);
  static at::Tensor max_unpool2d(const at::Tensor &self,
                                 const at::Tensor &indices,
                                 at::IntArrayRef output_size);
  static at::Tensor &max_unpool2d_backward_out(at::Tensor &grad_input,
                                               const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               const at::Tensor &indices,
                                               at::IntArrayRef output_size);
  static at::Tensor max_unpool2d_backward(const at::Tensor &grad_output,
                                          const at::Tensor &self,
                                          const at::Tensor &indices,
                                          at::IntArrayRef output_size);
  static at::Tensor &max_unpool3d_out(at::Tensor &out, const at::Tensor &self,
                                      const at::Tensor &indices,
                                      at::IntArrayRef output_size,
                                      at::IntArrayRef stride,
                                      at::IntArrayRef padding);
  static at::Tensor max_unpool3d(const at::Tensor &self,
                                 const at::Tensor &indices,
                                 at::IntArrayRef output_size,
                                 at::IntArrayRef stride,
                                 at::IntArrayRef padding);
  static at::Tensor &max_unpool3d_backward_out(at::Tensor &grad_input,
                                               const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               const at::Tensor &indices,
                                               at::IntArrayRef output_size,
                                               at::IntArrayRef stride,
                                               at::IntArrayRef padding);
  static at::Tensor
  max_unpool3d_backward(const at::Tensor &grad_output, const at::Tensor &self,
                        const at::Tensor &indices, at::IntArrayRef output_size,
                        at::IntArrayRef stride, at::IntArrayRef padding);
  static at::Tensor &reflection_pad1d_out(at::Tensor &out,
                                          const at::Tensor &self,
                                          at::IntArrayRef padding);
  static at::Tensor reflection_pad1d(const at::Tensor &self,
                                     at::IntArrayRef padding);
  static at::Tensor &reflection_pad1d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding);
  static at::Tensor reflection_pad1d_backward(const at::Tensor &grad_output,
                                              const at::Tensor &self,
                                              at::IntArrayRef padding);
  static at::Tensor &reflection_pad2d_out(at::Tensor &out,
                                          const at::Tensor &self,
                                          at::IntArrayRef padding);
  static at::Tensor reflection_pad2d(const at::Tensor &self,
                                     at::IntArrayRef padding);
  static at::Tensor &reflection_pad2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding);
  static at::Tensor reflection_pad2d_backward(const at::Tensor &grad_output,
                                              const at::Tensor &self,
                                              at::IntArrayRef padding);
  static at::Tensor &replication_pad1d_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           at::IntArrayRef padding);
  static at::Tensor replication_pad1d(const at::Tensor &self,
                                      at::IntArrayRef padding);
  static at::Tensor &replication_pad1d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding);
  static at::Tensor replication_pad1d_backward(const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               at::IntArrayRef padding);
  static at::Tensor &replication_pad2d_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           at::IntArrayRef padding);
  static at::Tensor replication_pad2d(const at::Tensor &self,
                                      at::IntArrayRef padding);
  static at::Tensor &replication_pad2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding);
  static at::Tensor replication_pad2d_backward(const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               at::IntArrayRef padding);
  static at::Tensor &replication_pad3d_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           at::IntArrayRef padding);
  static at::Tensor replication_pad3d(const at::Tensor &self,
                                      at::IntArrayRef padding);
  static at::Tensor &replication_pad3d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      const at::Tensor &self, at::IntArrayRef padding);
  static at::Tensor replication_pad3d_backward(const at::Tensor &grad_output,
                                               const at::Tensor &self,
                                               at::IntArrayRef padding);
  static at::Tensor &upsample_linear1d_out(at::Tensor &out,
                                           const at::Tensor &self,
                                           at::IntArrayRef output_size,
                                           bool align_corners);
  static at::Tensor upsample_linear1d(const at::Tensor &self,
                                      at::IntArrayRef output_size,
                                      bool align_corners);
  static at::Tensor &upsample_linear1d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size,
      bool align_corners);
  static at::Tensor upsample_linear1d_backward(const at::Tensor &grad_output,
                                               at::IntArrayRef output_size,
                                               at::IntArrayRef input_size,
                                               bool align_corners);
  static at::Tensor &upsample_bilinear2d_out(at::Tensor &out,
                                             const at::Tensor &self,
                                             at::IntArrayRef output_size,
                                             bool align_corners);
  static at::Tensor upsample_bilinear2d(const at::Tensor &self,
                                        at::IntArrayRef output_size,
                                        bool align_corners);
  static at::Tensor &upsample_bilinear2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size,
      bool align_corners);
  static at::Tensor upsample_bilinear2d_backward(const at::Tensor &grad_output,
                                                 at::IntArrayRef output_size,
                                                 at::IntArrayRef input_size,
                                                 bool align_corners);
  static at::Tensor &upsample_bicubic2d_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::IntArrayRef output_size,
                                            bool align_corners);
  static at::Tensor upsample_bicubic2d(const at::Tensor &self,
                                       at::IntArrayRef output_size,
                                       bool align_corners);
  static at::Tensor &upsample_bicubic2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size,
      bool align_corners);
  static at::Tensor upsample_bicubic2d_backward(const at::Tensor &grad_output,
                                                at::IntArrayRef output_size,
                                                at::IntArrayRef input_size,
                                                bool align_corners);
  static at::Tensor &upsample_trilinear3d_out(at::Tensor &out,
                                              const at::Tensor &self,
                                              at::IntArrayRef output_size,
                                              bool align_corners);
  static at::Tensor upsample_trilinear3d(const at::Tensor &self,
                                         at::IntArrayRef output_size,
                                         bool align_corners);
  static at::Tensor &upsample_trilinear3d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size,
      bool align_corners);
  static at::Tensor upsample_trilinear3d_backward(const at::Tensor &grad_output,
                                                  at::IntArrayRef output_size,
                                                  at::IntArrayRef input_size,
                                                  bool align_corners);
  static at::Tensor &upsample_nearest1d_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::IntArrayRef output_size);
  static at::Tensor upsample_nearest1d(const at::Tensor &self,
                                       at::IntArrayRef output_size);
  static at::Tensor &upsample_nearest1d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size);
  static at::Tensor upsample_nearest1d_backward(const at::Tensor &grad_output,
                                                at::IntArrayRef output_size,
                                                at::IntArrayRef input_size);
  static at::Tensor &upsample_nearest2d_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::IntArrayRef output_size);
  static at::Tensor upsample_nearest2d(const at::Tensor &self,
                                       at::IntArrayRef output_size);
  static at::Tensor &upsample_nearest2d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size);
  static at::Tensor upsample_nearest2d_backward(const at::Tensor &grad_output,
                                                at::IntArrayRef output_size,
                                                at::IntArrayRef input_size);
  static at::Tensor &upsample_nearest3d_out(at::Tensor &out,
                                            const at::Tensor &self,
                                            at::IntArrayRef output_size);
  static at::Tensor upsample_nearest3d(const at::Tensor &self,
                                       at::IntArrayRef output_size);
  static at::Tensor &upsample_nearest3d_backward_out(
      at::Tensor &grad_input, const at::Tensor &grad_output,
      at::IntArrayRef output_size, at::IntArrayRef input_size);
  static at::Tensor upsample_nearest3d_backward(const at::Tensor &grad_output,
                                                at::IntArrayRef output_size,
                                                at::IntArrayRef input_size);
  static at::Tensor &sigmoid_backward_out(at::Tensor &grad_input,
                                          const at::Tensor &grad_output,
                                          const at::Tensor &output);
  static at::Tensor sigmoid_backward(const at::Tensor &grad_output,
                                     const at::Tensor &output);
  static at::Tensor &tanh_backward_out(at::Tensor &grad_input,
                                       const at::Tensor &grad_output,
                                       const at::Tensor &output);
  static at::Tensor tanh_backward(const at::Tensor &grad_output,
                                  const at::Tensor &output);
  static at::Tensor &slow_conv_transpose2d_out(
      at::Tensor &out, const at::Tensor &self, const at::Tensor &weight,
      at::IntArrayRef kernel_size, const at::Tensor &bias,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation);
  static at::Tensor
  slow_conv_transpose2d(const at::Tensor &self, const at::Tensor &weight,
                        at::IntArrayRef kernel_size, const at::Tensor &bias,
                        at::IntArrayRef stride, at::IntArrayRef padding,
                        at::IntArrayRef output_padding,
                        at::IntArrayRef dilation);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  slow_conv_transpose2d_backward_out(
      at::Tensor &grad_input, at::Tensor &grad_weight, at::Tensor &grad_bias,
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation,
      const at::Tensor &columns, const at::Tensor &ones);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  slow_conv_transpose2d_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation,
      const at::Tensor &columns, const at::Tensor &ones,
      std::array<bool, 3> output_mask);
  static at::Tensor &slow_conv_transpose3d_out(
      at::Tensor &out, const at::Tensor &self, const at::Tensor &weight,
      at::IntArrayRef kernel_size, const at::Tensor &bias,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation);
  static at::Tensor
  slow_conv_transpose3d(const at::Tensor &self, const at::Tensor &weight,
                        at::IntArrayRef kernel_size, const at::Tensor &bias,
                        at::IntArrayRef stride, at::IntArrayRef padding,
                        at::IntArrayRef output_padding,
                        at::IntArrayRef dilation);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  slow_conv_transpose3d_backward_out(
      at::Tensor &grad_input, at::Tensor &grad_weight, at::Tensor &grad_bias,
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation,
      const at::Tensor &finput, const at::Tensor &fgrad_input);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  slow_conv_transpose3d_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef output_padding, at::IntArrayRef dilation,
      const at::Tensor &finput, const at::Tensor &fgrad_input,
      std::array<bool, 3> output_mask);
  static at::Tensor &thnn_conv2d_out(at::Tensor &out, const at::Tensor &self,
                                     const at::Tensor &weight,
                                     at::IntArrayRef kernel_size,
                                     const at::Tensor &bias,
                                     at::IntArrayRef stride,
                                     at::IntArrayRef padding);
  static at::Tensor thnn_conv2d(const at::Tensor &self,
                                const at::Tensor &weight,
                                at::IntArrayRef kernel_size,
                                const at::Tensor &bias, at::IntArrayRef stride,
                                at::IntArrayRef padding);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  thnn_conv2d_forward_out(at::Tensor &output, at::Tensor &finput,
                          at::Tensor &fgrad_input, const at::Tensor &self,
                          const at::Tensor &weight, at::IntArrayRef kernel_size,
                          const at::Tensor &bias, at::IntArrayRef stride,
                          at::IntArrayRef padding);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  thnn_conv2d_forward(const at::Tensor &self, const at::Tensor &weight,
                      at::IntArrayRef kernel_size, const at::Tensor &bias,
                      at::IntArrayRef stride, at::IntArrayRef padding);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  thnn_conv2d_backward_out(at::Tensor &grad_input, at::Tensor &grad_weight,
                           at::Tensor &grad_bias, const at::Tensor &grad_output,
                           const at::Tensor &self, const at::Tensor &weight,
                           at::IntArrayRef kernel_size, at::IntArrayRef stride,
                           at::IntArrayRef padding, const at::Tensor &finput,
                           const at::Tensor &fgrad_input);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  thnn_conv2d_backward(const at::Tensor &grad_output, const at::Tensor &self,
                       const at::Tensor &weight, at::IntArrayRef kernel_size,
                       at::IntArrayRef stride, at::IntArrayRef padding,
                       const at::Tensor &finput, const at::Tensor &fgrad_input,
                       std::array<bool, 3> output_mask);
  static at::Tensor &
  thnn_conv_depthwise2d_out(at::Tensor &out, const at::Tensor &self,
                            const at::Tensor &weight,
                            at::IntArrayRef kernel_size, const at::Tensor &bias,
                            at::IntArrayRef stride, at::IntArrayRef padding,
                            at::IntArrayRef dilation);
  static at::Tensor
  thnn_conv_depthwise2d(const at::Tensor &self, const at::Tensor &weight,
                        at::IntArrayRef kernel_size, const at::Tensor &bias,
                        at::IntArrayRef stride, at::IntArrayRef padding,
                        at::IntArrayRef dilation);
  static at::Tensor &thnn_conv_depthwise2d_forward_out(
      at::Tensor &out, const at::Tensor &self, const at::Tensor &weight,
      at::IntArrayRef kernel_size, const at::Tensor &bias,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef dilation);
  static at::Tensor thnn_conv_depthwise2d_forward(const at::Tensor &self,
                                                  const at::Tensor &weight,
                                                  at::IntArrayRef kernel_size,
                                                  const at::Tensor &bias,
                                                  at::IntArrayRef stride,
                                                  at::IntArrayRef padding,
                                                  at::IntArrayRef dilation);
  static std::tuple<at::Tensor &, at::Tensor &>
  thnn_conv_depthwise2d_backward_out(
      at::Tensor &grad_input, at::Tensor &grad_weight,
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding,
      at::IntArrayRef dilation);
  static std::tuple<at::Tensor, at::Tensor> thnn_conv_depthwise2d_backward(
      const at::Tensor &grad_output, const at::Tensor &self,
      const at::Tensor &weight, at::IntArrayRef kernel_size,
      at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation,
      std::array<bool, 2> output_mask);
  static at::Tensor &thnn_conv3d_out(at::Tensor &out, const at::Tensor &self,
                                     const at::Tensor &weight,
                                     at::IntArrayRef kernel_size,
                                     const at::Tensor &bias,
                                     at::IntArrayRef stride,
                                     at::IntArrayRef padding);
  static at::Tensor thnn_conv3d(const at::Tensor &self,
                                const at::Tensor &weight,
                                at::IntArrayRef kernel_size,
                                const at::Tensor &bias, at::IntArrayRef stride,
                                at::IntArrayRef padding);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  thnn_conv3d_forward_out(at::Tensor &output, at::Tensor &finput,
                          at::Tensor &fgrad_input, const at::Tensor &self,
                          const at::Tensor &weight, at::IntArrayRef kernel_size,
                          const at::Tensor &bias, at::IntArrayRef stride,
                          at::IntArrayRef padding);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  thnn_conv3d_forward(const at::Tensor &self, const at::Tensor &weight,
                      at::IntArrayRef kernel_size, const at::Tensor &bias,
                      at::IntArrayRef stride, at::IntArrayRef padding);
  static std::tuple<at::Tensor &, at::Tensor &, at::Tensor &>
  thnn_conv3d_backward_out(at::Tensor &grad_input, at::Tensor &grad_weight,
                           at::Tensor &grad_bias, const at::Tensor &grad_output,
                           const at::Tensor &self, const at::Tensor &weight,
                           at::IntArrayRef kernel_size, at::IntArrayRef stride,
                           at::IntArrayRef padding, const at::Tensor &finput,
                           const at::Tensor &fgrad_input);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  thnn_conv3d_backward(const at::Tensor &grad_output, const at::Tensor &self,
                       const at::Tensor &weight, at::IntArrayRef kernel_size,
                       at::IntArrayRef stride, at::IntArrayRef padding,
                       const at::Tensor &finput, const at::Tensor &fgrad_input,
                       std::array<bool, 3> output_mask);
  static at::Tensor
  slow_conv_dilated2d(const at::Tensor &self, const at::Tensor &weight,
                      at::IntArrayRef kernel_size, const at::Tensor &bias,
                      at::IntArrayRef stride, at::IntArrayRef padding,
                      at::IntArrayRef dilation);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  slow_conv_dilated2d_backward(const at::Tensor &grad_output,
                               const at::Tensor &self, const at::Tensor &weight,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation,
                               std::array<bool, 3> output_mask);
  static at::Tensor
  slow_conv_dilated3d(const at::Tensor &self, const at::Tensor &weight,
                      at::IntArrayRef kernel_size, const at::Tensor &bias,
                      at::IntArrayRef stride, at::IntArrayRef padding,
                      at::IntArrayRef dilation);
  static std::tuple<at::Tensor, at::Tensor, at::Tensor>
  slow_conv_dilated3d_backward(const at::Tensor &grad_output,
                               const at::Tensor &self, const at::Tensor &weight,
                               at::IntArrayRef kernel_size,
                               at::IntArrayRef stride, at::IntArrayRef padding,
                               at::IntArrayRef dilation,
                               std::array<bool, 3> output_mask);
  static at::Tensor &col2im_out(at::Tensor &out, const at::Tensor &self,
                                at::IntArrayRef output_size,
                                at::IntArrayRef kernel_size,
                                at::IntArrayRef dilation,
                                at::IntArrayRef padding,
                                at::IntArrayRef stride);
  static at::Tensor col2im(const at::Tensor &self, at::IntArrayRef output_size,
                           at::IntArrayRef kernel_size,
                           at::IntArrayRef dilation, at::IntArrayRef padding,
                           at::IntArrayRef stride);
  static at::Tensor &
  col2im_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                      at::IntArrayRef kernel_size, at::IntArrayRef dilation,
                      at::IntArrayRef padding, at::IntArrayRef stride);
  static at::Tensor col2im_backward(const at::Tensor &grad_output,
                                    at::IntArrayRef kernel_size,
                                    at::IntArrayRef dilation,
                                    at::IntArrayRef padding,
                                    at::IntArrayRef stride);
  static at::Tensor &im2col_out(at::Tensor &out, const at::Tensor &self,
                                at::IntArrayRef kernel_size,
                                at::IntArrayRef dilation,
                                at::IntArrayRef padding,
                                at::IntArrayRef stride);
  static at::Tensor im2col(const at::Tensor &self, at::IntArrayRef kernel_size,
                           at::IntArrayRef dilation, at::IntArrayRef padding,
                           at::IntArrayRef stride);
  static at::Tensor &
  im2col_backward_out(at::Tensor &grad_input, const at::Tensor &grad_output,
                      at::IntArrayRef input_size, at::IntArrayRef kernel_size,
                      at::IntArrayRef dilation, at::IntArrayRef padding,
                      at::IntArrayRef stride);
  static at::Tensor
  im2col_backward(const at::Tensor &grad_output, at::IntArrayRef input_size,
                  at::IntArrayRef kernel_size, at::IntArrayRef dilation,
                  at::IntArrayRef padding, at::IntArrayRef stride);
};

void RegisterAtenTypeFunctions();

} // namespace torch_mlir
