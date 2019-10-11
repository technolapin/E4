test = {
  'name': 'tanh_model',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.random.seed(42);
          >>> 
          >>> x = np.linspace(-1,1, 5);
          >>> w = [0.5, 1., 1., 0.5];
          >>> 
          >>> tanh_model(x, w)
          array([0.96211716, 1.13514895, 1.26159416, 1.34828364, 1.40514825])
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
