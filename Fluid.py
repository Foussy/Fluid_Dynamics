class Fluid:
    def __init__(self, dt, diffusion, viscosity):
        self.dt = dt
        self.diffusion = diffusion
        self.viscosity = viscosity